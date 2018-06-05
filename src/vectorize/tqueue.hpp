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
        void stop();
    protected:
        void process(size_t beg_index, size_t end_index);
    private:
        void start(bool sync);

        // Queue of jobs that must be completed
        std::mutex jobs_mut;
        std::vector<job<R,A>> jobs;

        // Condition variable used to wake/pause threads
        std::condition_variable job_cond;

        // Is true while working, otherwise is set to false
        job_callee<R,A> func;

        size_t thread_count;
        size_t running_threads {0};
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
    for (auto &j : _jobs)
    {
        job<R,A> new_job {std::move(j)};
        jobs.emplace_back(std::move(new_job));
    }
}

// DESTRUCTOR
template<typename R, typename A>
thread_queue<R,A>::~thread_queue()
{
    std::lock_guard<std::mutex> jobs_lock(jobs_mut);
    this->stop();
}

// Start the number of threads, then wait for them to notify the main thread.
// When they are all finished the main thread will continue
template<typename R, typename A>
void thread_queue<R,A>::start()
{
    if (threads) return;

    std::unique_lock<std::mutex> jobs_lock(jobs_mut);
    threads = new std::thread[thread_count];
    running_threads = thread_count;

    // Calculate the increment size
    size_t increment_size = jobs.size() / (thread_count+1);
    size_t i;
    // Delegate jobs out to each processing thread.
    for (i=0; i < thread_count; ++i)
    {
        threads[i] = std::thread(&thread_queue<R,A>::process, \
            this, \
            i*increment_size, i*increment_size+increment_size);
    }
    // "Wrap up" the jobs. Finish the last batch on the main thread
    process(i*increment_size, jobs.size() - 1);

    // Wait for all threads to finish and for main thread to be notified
    job_cond.wait(jobs_lock, [&]{return running_threads > 0;}); // TODO(nick) change wait to wait_for

    this->stop();
}

// Stop all threads and delete the array of threads (and set to nullptr)
template<typename R, typename A>
void thread_queue<R,A>::stop()
{
    if (!threads) return;

    for (int i=0; i < thread_count; ++i)
    {
        if (threads[i].joinable())
            threads[i].join();
    }
    delete [] threads;
    threads = nullptr;
}

template<typename R, typename A>
void thread_queue<R,A>::process(size_t beg_index, size_t end_index)
{
    auto beg = jobs.begin() + beg_index;
    auto end = jobs.end() - (jobs.size() - end_index);

    for (; beg != end; ++beg)
        beg->start(func);

    --running_threads;
    job_cond.notify_one();
}