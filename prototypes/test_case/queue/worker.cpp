#include "worker.h"

/* Constructor*/
template<class R, class A>
worker<R,A>::worker(worker_func<R,A> _func, const A& _args) :
    func(_func),
    args(_args)
{
}
/* Constructor by moving arguments */
template<class R, class A>
worker<R,A>::worker(worker_func<R,A> _func, A &&_args) :
    func(_func),
    args(std::move(_args))
{

}
/* Set the arguments for the function*/
template<class R, class A>
worker<R,A>& worker<R,A>::set_args(const A &_args)
{
    args = _args;
}
/* Set the arguments for the function by moving them*/
template<class R, class A>
worker<R,A>& worker<R,A>::set_args(A &&_args)
{
    args = std::move(_args);
}

/* Start running the function and store the result */
template<class R, class A>
void worker<R,A>::start()
{
    result = func(args);
}