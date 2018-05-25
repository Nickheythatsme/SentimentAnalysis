/*
 * 5/23/2018
 *
 * A single worker which calls the function with specified arguments,
 * and stores the result. It starts a thread with the current arguments,
 * and blocks all output/input until the thread is finished.
 */
#include <atomic>
#include <thread>
#include <vector>
#include <condition_variable>
#include "job.h"

#ifndef QUEUE_WORKER_
#define QUEUE_WORKER_

using std::thread;
using std::atomic;
using std::vector;

/*
 // TODO remove. This is only for reference
 
// We need job's args object to not be a reference, used in some arguments
template<class A>
using deRef = typename std::remove_reference<A>::type;

// We need job's args object to be modifyable, so we remove the const
template<class A>
using deConstRef = typename std::remove_const<deRef<A>>::type;

*/

template<class R, class A>
class worker
{
    public:
        worker();
        worker(const worker<R,A> &rhs);
        worker(worker<R,A> &&rhs);
        ~worker();
    protected:
    private:
        std::atomic_bool running;
        std::mutex;
        std::queue<job<R,A>> data_queue;
};

#include "worker.cpp"
#endif // QUEUE_WORKER_
