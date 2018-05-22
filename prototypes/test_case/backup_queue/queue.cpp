#include "queue.h"

template <typename F, typename A>
uint queue<F,A>::max_num_workers = std::thread::hardware_concurrency();

// CONSTRUCTOR
template <typename F, typename A>
queue<F,A>::queue() : 
    args()
{
    num_workers = 0;
    function = nullptr;
}

// COPY CONSTRUCTOR
template <typename F, typename A>
queue<F,A>::queue(const queue &obj) : 
    args(obj.args),
    function(obj.function)
{
    num_workers = obj.num_workers;
}

// CONSTRUCTOR with arguments
template <typename F, typename A>
queue<F,A>::queue(F *_function, std::vector<A> _args) : 
    args(_args),
    function(_function),
    num_workers(max_num_workers)
{
    num_workers = max_num_workers;
}

// CONSTRUCTOR with arguments
template <typename F, typename A>
queue<F,A>::queue(F *_function, std::vector<A> _args, uint _num_workers) :
    args(_args),
    function(_function),
    num_workers(_num_workers)
{
}

// DESTRUCTOR
template <typename F, typename A>
queue<F,A>::~queue()
{
}

// Start processing every argument in the vector
template <typename F, typename A>
const std::vector<A>& queue<F,A>::start()
{
    std::lock_guard<std::mutex> g(qlock);

    auto workers = new worker<F,A>[num_workers];
    uint increment = args.size() / num_workers;
    uint mod       = args.size() % num_workers;
    uint i_arg     = 0;
    uint i_worker  = 0;

    /*
    workers[i_worker].run(function, args, i_arg, i_arg + increment + mod - 1);
    ++i_worker;
    i_arg += increment;
    */

    for(;i_worker < num_workers - 1; ++i_worker, i_arg += increment)
    {
        workers[i_worker].run(function, args, i_arg, i_arg + increment - 1);
    }

    workers[i_worker].run_block(function, args, i_arg, i_arg + increment + mod - 1);
    /*
    ++i_worker;
    i_arg += increment + mod - 1;
    */

    delete [] workers;
    return args;
}

template <typename F, typename A>
uint queue<F,A>::worker_count() const
{
    return num_workers;
}
