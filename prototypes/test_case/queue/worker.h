#include <atomic>
#include <mutex>

#ifndef QUEUE_WORKER_
#define QUEUE_WORKER_

using std::mutex;

template<class R, class A>
using worker_func = R (*)(A);

template<class R, class A>
class worker
{
    public:
        worker(worker_func<R,A> _func, const A &args);
        worker(worker_func<R,A> _func, A &&args);
        worker(const worker<R,A> &obj) = delete;
        worker(worker<R,A> && obj) = delete;
        ~worker() = default;
        worker<R,A>& set_args(const A &args);
        worker<R,A>& set_args(A &&args);
        void start();
        const R& get_result() {return result;}
    protected:
    private:
        worker_func<R,A> func;
        R result;
        A args;
};

#include "worker.cpp"
#endif // QUEUE_WORKER_