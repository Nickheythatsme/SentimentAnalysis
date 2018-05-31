/*
    5/31/2018 Nicholas Grout

    This base class runs on one thread, and processes data from 
    the queue (using locks). The processing depends on a condition_variable,
    which is handled by the derived class. This base class will be stopped
    and started by the derived class.
*/


#ifndef SENTIMENTANALYSIS_PROTOTYPES_QUEUE_WORKER_CPP
#define SENTIMENTANALYSIS_PROTOTYPES_QUEUE_WORKER_CPP

#include <type_traits>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

// We need job's args object to not be a reference, used in some arguments
template<class A>
using deref = typename std::remove_reference<A>::type;

/*
 * Define the function which is to be called by the job
 */
template<class R, class A>
using job_callee = R (*)(A);

template<typename R, typename A>
struct worker_tools
{
    std::mutex& jobs_mut;
    std::queue<deref<A>>& jobs;

    std::mutex& finished_mut; 
    std::vector<deref<R>>& finished;
    job_callee<R,A> func;
};


template<typename R, typename A>
class worker
{
    public:
        worker() = delete;
        worker(job_callee<R,A> _func, 
                std::mutex& _jobs_mut,
                std::queue<deref<A>>& _jobs,
                std::mutex& _finished_mut,
                std::vector<deref<A>>& _finished);
        worker(const worker<R,A> &rhs) = delete;
        worker(worker<R,A> &&rhs) = delete;
        ~worker() = default;
        worker<R,A>& operator=(const worker<R,A> &rhs) = delete;
        worker<R,A>& operator=(worker<R,A> &&rhs) = delete;
        void start_job();
    protected:
    private:
        std::mutex& jobs_mut;
        std::queue<deref<A>>& jobs;

        std::mutex& finished_mut; 
        std::vector<deref<R>>& finished;
        job_callee<R,A> func;
};

// CONSTRUCTOR
template<typename R, typename A>
worker<R,A>::worker(job_callee<R,A> _func,
        std::mutex& _jobs_mut,
        std::queue<deref<A>>& _jobs,
        std::mutex& _finished_mut,
        std::vector<deref<R>>& _finished) :
    func(_func),
    jobs_mut(_jobs_mut),
    jobs(_jobs),
    finished_mut(_finished_mut),
    finished(_finished)
{
}

template<typename R, typename A>
void worker<R,A>::start_job()
{
    // Lock and get the next job
    std::unique_lock<std::mutex> jobs_lock(jobs_mut);
    deref<A> current_job {std::move(jobs.front())};
    jobs.pop();
    jobs_lock.unlock();

    // Do the job
    deref<R> return_val = func(current_job);

    // Lock and move the return value into the return vector
    std::lock_guard<std::mutex> finished_lock(finished_mut);
    finished.emplace_back(std::move(return_val));
}

#endif // SENTIMENTANALYSIS_PROTOTYPES_QUEUE_WORKER_CPP