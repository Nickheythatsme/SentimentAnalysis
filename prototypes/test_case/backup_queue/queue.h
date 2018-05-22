#include "worker.h"
#include <mutex>

#ifndef QUEUE_
#define QUEUE_

template <typename F, typename A>
class queue 
{
    public:
        queue();
        explicit queue(F *_function, std::vector<A> _args);
        explicit queue(F *_function, std::vector<A> _args, uint workers);
        queue(const queue<F,A> &obj);
        ~queue();
        const std::vector<A>& start();
        uint worker_count() const;
    protected:
    private:
        F *function;
        std::vector<A> args;
        std::mutex qlock;
        uint num_workers;

        static uint max_num_workers;
};

#include "queue.cpp"
#endif //QUEUE_
