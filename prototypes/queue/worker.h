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
#include "job.h"

#ifndef QUEUE_WORKER_
#define QUEUE_WORKER_

using std::thread;
using std::atomic;
using std::vector;


template<class R, class A>
class worker
{
    public:
    protected:
    private:
        atomic_bool running;
};

#include "worker.cpp"
#endif // QUEUE_WORKER_
