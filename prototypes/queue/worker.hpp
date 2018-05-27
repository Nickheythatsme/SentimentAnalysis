#ifndef QUEUE_WORKER_
#include QUEUE_WORKER_


#include <condition_variable>
#include <atomic>

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
        std::queue<R
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
