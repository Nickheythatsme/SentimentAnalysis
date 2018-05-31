/*
 * 5/23/2018
 *
 * This is the job class. Each item in the queue will be a package, which
 * will store the function, the arguments, and the return value.
 */

#ifndef SENTIMENTANALYSIS_PROTOTYPES_QUEUE_JOB_CPP
#define SENTIMENTANALYSIS_PROTOTYPES_QUEUE_JOB_CPP

#include <type_traits>
#include <utility>

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
        job(job_callee<R,A> _callee, deConstRef<A> &&_args);
        job(job_callee<R,A> _callee, const A &_args);
        job(job<R,A> &&rhs);
        ~job() = default;

        // Get the return value
        R&& get_return_val();

        // Set the args for the function
        job<R,A>& set_args(deConstRef<A>&& _args);
        job<R,A>& set_args(const A &_args);

        // Return the arguments
        A&& get_args();

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

// CONSTRUCTOR
template<typename R, typename A>
job<R,A>::job(job_callee<R,A> _callee, deConstRef<A> &&_args) :
    callee(_callee),
    args(std::move(_args))
{
}

// CONSTRUCTOR
template<typename R, typename A>
job<R,A>::job(job_callee<R,A> _callee, const A &_args) :
    callee(_callee),
    args(_args)
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
R&& job<R,A>::get_return_val()
{
    return std::move(return_val);
}

template<typename R, typename A>
job<R,A>& job<R,A>::set_args(const A &_args)
{
    args = _args;
    return *this;
}

// Move arguments into our arguments
template<typename R, typename A>
job<R,A>& job<R,A>::set_args(deConstRef<A> &&_args)
{
    args = deRef<A>(std::move(_args));
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

#endif // SENTIMENTANALYSIS_PROTOTYPES_QUEUE_JOB_CPP
