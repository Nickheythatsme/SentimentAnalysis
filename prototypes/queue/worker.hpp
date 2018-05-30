/*
 * 5/27/2018 Nick Grout
 *
 * This class manages one thread, completing a job at a time until indicated to stop, or until the queue is empty.
 * We use condition_variables to determine whether the queue has data in it. The condition is called by the
 * manager class, thread_queue (in separate file). This way we don't eat up processor time and we also don't
 * need to wait until the next cycle to check if data exists.
 *
 * We use atomic variables and mutexes to ensure that there are no race conditions surrounding our queue.
 */
#ifndef QUEUE_WORKER_
#define QUEUE_WORKER_

#include <condition_variable>
#include <atomic>
#include <mutex>
#include <queue>
#include <chrono>
#include "job.hpp"

// TODO remove when not debugging
#include <iostream> 

template<typename R, typename A>
class worker
{
    public:
        worker() = delete;
        worker(std::mutex& _jobs_mut, 
                std::queue<job<R,A>>& _jobs,
                std::mutex& _ret_vals_mut,
                std::vector<deConstRef<R>>& _ret_vals,
                std::condition_variable& _data_cond);
        worker(const worker<R,A> &rhs) = delete;
        worker(worker<R,A> &&rhs) = delete;
        ~worker() = default;
        void stop_working() {working = false;}
        void start_working();
        bool is_working() {return working;}

        std::atomic_bool working {false};
    protected:
    private:
        void process_jobs();
        // Set to true if we're working, otherwise this is false

        // Queue for upcoming jobs and its mutex
        std::queue<job<R,A>>& jobs;
        std::mutex& jobs_mut;

        // Vector for finished jobs and its mutex
        std::vector<deConstRef<R>>& ret_vals;
        std::mutex& ret_vals_mut;

        // Data condition condition_varible. Used to enable waiting for workers
        std::condition_variable& data_cond;
};

// CONSTRUCTOR
template<typename R, typename A>
worker<R,A>::worker(std::mutex& _jobs_mut, 
        std::queue<job<R,A>>& _jobs,
        std::mutex& _ret_vals_mut,
        std::vector<deConstRef<R>>& _ret_vals,
        std::condition_variable& _data_cond) :
    jobs_mut(_jobs_mut),
    jobs(_jobs),
    ret_vals_mut(_ret_vals_mut),
    ret_vals(_ret_vals),
    data_cond(_data_cond)
{
}

/*
 * Make the worker start processing threads from the queue, sets the 'working'
 * boolean variable to true
 */
template<typename R, typename A>
void worker<R,A>::start_working()
{
    working = true;
    process_jobs();
}

/*
 * Process jobs in the queue, or wait until we're notified to work. 
 * Continue the loop while and wait to be notified
 */
// TODO change to wait_until rather than wait. This requires an additional
// check for the queue before we pop/get front
template<typename R, typename A>
void worker<R,A>::process_jobs()
{
    while (working == true)
    {
        std::cout << "....Working? " << working << std::endl;

        // Get the current job and lock the queue while popping
        std::unique_lock<std::mutex> loop_lock(jobs_mut);

        // Lock this thread and wait to be notified
        std::cout << "....Waiting" << std::endl;
        data_cond.wait(
                loop_lock, [&]{return !jobs.empty();});
        std::cout << "....Done waiting" << std::endl;

        // Get an upcoming job while we have the lock
        if (!jobs.empty())
        {
            job<R,A> current_job = std::move(jobs.front());
            jobs.pop();
            std::cout << "....Starting job: " << std::endl;
            current_job.start();

            // Work on the current job
            std::unique_lock<std::mutex> ret_lock(ret_vals_mut);
            ret_vals.emplace_back(std::move(current_job.get_return_val()));
            ret_lock.unlock();
        }
        loop_lock.unlock(); // unlock the jobs queue

    }
}

#endif // QUEUE_WORKER_
