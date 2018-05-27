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
#include QUEUE_WORKER_

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
        worker();
        worker(const worker<R,A> &rhs);
        worker(worker<R,A> &&rhs);
        ~worker();
    protected:
    private:
        std::queue<job<R,A>> jobs;
};

template<typename R, typename A>
worker<R, A>::worker() {

}
template<typename R, typename A>
worker<R, A>::worker(const worker<R, A> &rhs) {

}
template<typename R, typename A>
worker<R, A>::worker(worker<R, A> &&rhs) {

}
template<typename R, typename A>
worker<R, A>::~worker() {

}

#endif // QUEUE_WORKER_
