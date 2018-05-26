#include "job.h"
#include <queue>
#include <thread>
#include <vector>

#ifndef QUEUE_QUEUE_BASE
#define QUEUE_QUEUE_BASE

template<typename R, typename A>
class queue_base
{
    public:
        queue_base();
        explicit queue_base(std::vector<deRef<A>> && args, size_t threads=0);
        queue_base(const queue_base<R,A> &rhs);
        queue_base(queue_base<R,A> &&rhs);
        ~queue_base();
    protected:
        void add_job(job<R,A> &&j);
        void add_arg(deRef<A> &&a);
    private:
        size_t thread_count;
        std::queue<job<R,A>> jobs;
        std::vector<deRef<R>> finished;
        static size_t choose_thread_count(size_t arg_size);
};

#include "queue_base.cpp"
#endif // QUEUE_QUEUE_BASE