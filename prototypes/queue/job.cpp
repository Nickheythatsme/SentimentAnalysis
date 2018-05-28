#include "job.h"

// CONSTRUCTOR with arguments
template<typename R, typename A>
job<R,A>::job(job_callee<R,A> _callee, const deRef<A> &_args) :
    callee(_callee),
    args(_args)
{
}

template<typename R, typename A>
job<R,A>::job(job_callee<R,A> _callee, deRef<A> &&_args) :
    callee(_callee),
    args(std::forward<deRef<A>>(_args))
{
}

// MOVE CONSTRUCTOR
template<typename R, typename A>
job<R,A>::job(job<R,A> &&rhs) :
    callee(rhs.callee),
    args(std::move(rhs.args))
{
}

// Move the return value from this job
template<typename R, typename A>
decltype(auto) job<R,A>::get_return_val()
{
    return std::move(return_val);
}

// return the return value from the last call to the function
template<typename R, typename A>
const R& job<R,A>::get_return_val() const
{
    return return_val;
}

// Copy arguments into our arguments
template<typename R, typename A>
job<R,A>& job<R,A>::set_args(const deRef<A>& _args)
{
    args = _args;
}

// Move arguments into our arguments
template<typename R, typename A>
job<R,A>& job<R,A>::set_args(deRef<A> &&_args)
{
    args = deRef<A>(std::forward<A>(_args));
}

// Return the arguments for this given job. Useful if the arguments change after the function call
template<typename R, typename A>
const A& job<R,A>::get_args() const
{
    return args;
}

// Move our arguments out of this object
template<typename R, typename A>
A&& job<R,A>::get_args()
{
    return std::move(args);
}


// Set the function to call
template<typename R, typename A>
job<R,A>& job<R,A>::set_func(const job_callee<R,A> &_callee)
{
    callee = _callee;
    return *this;
}

// Start the function
template<typename R, typename A>
void job<R,A>::start()
{
    return_val = callee(args);
}
