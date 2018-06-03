/*
5/31/2018 Nicholas Grout

This class is a threaded queue. It uses as many threads as are indicated to complete all of the jobs in the queue. Jobs are made
from a queue of arguments, and a pointer to a desiered function. The function may take constant references, references, or rvalues.
This queue can either start processing and allow the main thread to continue, or block the main thread until processing has completed.
*/
#include "tqueue_job.hpp"
#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <vector>
#include <chrono>
#include <iostream>

template<typename R, typename A>
class thread_queue
{
    public:
        thread_queue();
        thread_queue(job_callee<R,A> _func, 
            std::vector<deconstref<A>>&& _jobs, 
            size_t _thread_count);
        thread_queue(const thread_queue& rhs);
        thread_queue(thread_queue&& rhs);
        ~thread_queue();
        void start();
    protected:
        void process();
    private:
        void start(bool sync);

        // Queue of jobs that must be completed
        std::mutex jobs_mut;
        std::vector<job<R,A>> jobs;

        // Condition variable used to wake/pause threads
        std::condition_variable job_cond;

        // Is true while working, otherwise is set to false
        std::atomic_bool working {false};
        job_callee<R,A> func;

        size_t thread_count;
        size_t running_threads;
        std::thread *threads {nullptr};
};

// CONSTRUCTOR
template<typename R, typename A>
thread_queue<R,A>::thread_queue(job_callee<R,A> _func, 
            std::vector<deconstref<A>>&& _jobs, 
            size_t _thread_count) :
    func(_func),
    thread_count(_thread_count)
{
    // Move the queue of arguments into the job queue
    std::lock_guard<std::mutex> jobs_lock(jobs_mut);
    while (!arguments.empty())
    {
        job<R,A>&& new_job {std::move(arguments.front())};
        jobs.push( std::move(new_job) );
        arguments.pop();
    }
}

// DESTRUCTOR
template<typename R, typename A>
thread_queue<R,A>::~thread_queue()
{
    this->stop();
}

// Start thread number of threads, and then notify them to 
// start working.
template<typename R, typename A>
void thread_queue<R,A>::start()
{
    if (threads) return;

    threads = new std::thread[thread_count];
    for (int i=0; i < thread_count; ++i)
        threads[i] = std::thread(&thread_queue<R,A>::process, std::ref(*this));
    working = true;
    job_cond.notify_all();
}

// Start thread number of threads, and then notify them to 
// start working. WAIT until the queue is empty before exiting function
template<typename R, typename A>
void thread_queue<R,A>::start_sync()
{
    if (threads) return;

    threads = new std::thread[thread_count];
    working = true;
    for (int i=0; i < thread_count; ++i)
        threads[i] = std::thread(&thread_queue<R,A>::process_no_block, std::ref(*this));

    int threads_left = thread_count;
    while (threads_left > 0)
    {
        for (int i=0; i < thread_count; ++i)
            if (threads[i].joinable())
            {
                threads[i].join();
                --threads_left;
            }
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    delete [] threads;
    threads = nullptr;
}

// Stop all threads and delete the array of threads (and set to nullptr)
template<typename R, typename A>
void thread_queue<R,A>::stop()
{
    if (!threads) return;

    working = false;
    job_cond.notify_all();
    for (int i=0; i < thread_count; ++i)
        if (threads[i].joinable())
            threads[i].join();
    delete [] threads;
    threads = nullptr;
}

template<typename R, typename A>
void thread_queue<R,A>::process()
{
    while (working)
    {
        std::unique_lock<std::mutex> jobs_lock(jobs_mut);

        job_cond.wait(
            jobs_lock, [&]{return !jobs.empty() || !working;}
        );

        if (!working) break;

        job<R,A> current_job { std::move(jobs.front()) };
        jobs.pop();
        jobs_lock.unlock();

        // Make the function call
        current_job.start(func);
        
        std::unique_lock<std::mutex> finished_lock(finished_mut);
        finished.emplace_back(std::move(current_job));
    }
}

template<typename R, typename A>
void thread_queue<R,A>::process_no_block()
{
    while (!jobs.empty() && working)
    {
        std::unique_lock<std::mutex> jobs_lock(jobs_mut);

        if (jobs.empty()) return;
        job<R,A> current_job { std::move(jobs.front()) };
        jobs.pop();
        jobs_lock.unlock();

        // Make the function call
        current_job.start(func);

        std::unique_lock<std::mutex> finished_lock(finished_mut);
        finished.emplace_back(std::move(current_job));
    }
}