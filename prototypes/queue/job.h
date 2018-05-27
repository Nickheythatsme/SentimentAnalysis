/*
 * 5/23/2018
 *
 * This is the job class. Each item in the queue will be a package, which
 * will store the function, the arguments, and the return value.
 */

#ifndef QUEUE_JOB_
#define QUEUE_JOB_

#include <type_traits>

// We need job's args object to not be a reference, used in some arguments
template<class A>
using deRef = typename std::remove_reference<A>::type;

// We need job's args object to be modifyable, so we remove the const
template<class A>
using deConstRef = typename std::remove_const<deRef<A>>::type;

/*
 * Define the function which is to be called by the job
 */
template<class R, class A>
using job_callee = R (*)(A);

// Job class definition
template<typename R, typename A>
class job
{
public:
    job() = delete;
    job(job_callee<R,A> _callee, const deRef<A> &_args);
    job(job_callee<R,A> _callee, deRef<A> &&_args);
    job(job<R,A> &&rhs);
    ~job() = default;

    // Get the return value
    decltype(auto) get_return_val();
    const R& get_return_val() const;

    // Set the args for the function
    job<R,A>& set_args(deRef<A>&& args);
    job<R,A>& set_args(const deRef<A>& args);

    // Return the arguments
    A&& get_args();
    const A& get_args() const;

    // Set the function to call
    job<R,A>& set_func(const job_callee<R,A> &_callee);

    // Start the function
    void start();
protected:
private:
    R return_val;
    deConstRef<A> args;
    job_callee<R,A> callee;
};

#include "job.cpp"
#endif // QUEUE_JOB_
