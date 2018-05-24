#include "job.h"

// CONSTRUCTOR with arguments
template<class R, class A>
job<R,A>::job(job_callee<R,A> _callee) :
    callee(_callee),
    args()
{
}

template<class R, class A>
job<R,A>::job(job_callee<R,A> _callee, A &&_args) :
    callee(_callee),
    args(std::forward<A>(_args))
{
}

// MOVE CONSTRUCTOR
template<class R, class A>
job<R,A>::job(job<R,A> &&rhs) :
    callee(rhs.callee),
    args(std::move(rhs.args))
{
}

// Move the return value from this job
template<class R, class A>
decltype(auto) job<R,A>::get_return_val()
{
    return std::move(return_val);
}

template<class R, class A>
const R& job<R,A>::get_return_val() const
{
    return return_val;
}

// Move arguments into our arguments
template<class R, class A>
void job<R,A>::set_args(A &&_args)
{
    deref<A> temp = std::forward<A>(_args);

    std::cout << "Is rvalue: " << std::is_rvalue_reference<A>::value << std::endl;
    std::cout << "Is lvalue: " << std::is_lvalue_reference<A>::value << std::endl;

    std::cout << "Is reference: " << std::is_same<A, deref<A>>::value << std::endl;

    // args = deref<A>(std::forward<A>(_args));
}

// Return the arguments for this given job. Useful if the arguments change after the function call
template<class R, class A>
const A& job<R,A>::get_args() const
{
    return args;
}

// Move our arguments out of this object
template<class R, class A>
A&& job<R,A>::get_args()
{
    return std::move(args);
}


// Set the function to call
template<class R, class A>
job<R,A>& job<R,A>::set_func(const job_callee<R,A> _callee)
{
    callee = _callee;
    return *this;
}

// Start the function
template<class R, class A>
void job<R,A>::start()
{
    return_val = callee(args);
}
