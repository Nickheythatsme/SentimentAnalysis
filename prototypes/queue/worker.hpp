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
#include "job.hpp"

// TODO finish implementation
template<typename R, typename A>
class worker
{
    public:
        worker() = delete;
        worker(std::mutex &jobs_lock, std::queue<job<R,A>> &jobs);
        worker(const worker<R,A> &rhs) = delete;
        worker(worker<R,A> &&rhs) = delete;
        ~worker() = default;
        void stop_working() {working = false;}
        void start_working();
        bool is_working() {return working;}
    protected:
    private:
        void process_jobs();
        std::queue<job<R,A>>& jobs;
        std::mutex& jobs_lock;
        std::atomic_bool working {false};
        std::condition_variable data_cond; // TODO make this reference
        std::vector<deConstRef<R>> return_vals; // TODO make this reference
};

template<typename R, typename A>
worker<R,A>::worker(std::mutex &_jobs_lock, std::queue<job<R,A>> &_jobs) :
    jobs(_jobs),
    jobs_lock(_jobs_lock),
    data_cond(),
    return_vals()
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
template<typename R, typename A>
void worker<R,A>::process_jobs()
{
    while (working)
    {
        // Get the current job and lock the queue while popping
        std::unique_lock<std::mutex> loop_lock(jobs_lock);
        // Lock this thread and wait to be notified
        data_cond.wait(
                loop_lock, [&]{return !jobs.empty();});
        job<R,A> current_job = std::move(jobs.front());
        jobs.pop();
        loop_lock.unlock(); // unlock the jobs queue

        // Work on the current job
        current_job.start();
        return_vals.emplace_back(std::move(current_job.get_return_val()));
    }
}

#endif // QUEUE_WORKER_
