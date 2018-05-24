/*
 * 5/23/2018
 *
 * This is the package class. Each item in the queue will be a package, which
 * will store the function, the arguments, and the return value.
 */

#ifndef QUEUE_PACKAGE_
#define QUEUE_PACKAGE_

#include <mutex>
#include <atomic>

template<class R, class A>
using job_callee = R (*)(A);

template<class R, class A>
class job
{
public:
    job() = delete;
    job(job_callee<R,A> _callee);
    job(job_callee<R,A> _callee, A &&_args);
    job(job<R,A> &&rhs);
    ~job() = default;

    // Get the return value
    decltype(auto) get_return_val();
    const R& get_return_val() const;

    // Set the args for the function
    void set_args(A&& args);

    // Return the arguments
    A&& get_args();
    const A& get_args() const;

    // Set the function to call
    job<R,A>& set_func(const job_callee<R,A> _callee);

    // Start the function
    void start();
protected:
private:
    R return_val;
    A args;
    job_callee<R,A> callee;
};

#include "job.cpp"
#endif // QUEUE_PACKAGE_
