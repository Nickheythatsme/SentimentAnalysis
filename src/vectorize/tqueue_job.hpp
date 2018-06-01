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
using deref = typename std::remove_reference<A>::type;

// We need job's args object to be modifyable, so we remove the const
template<class A>
using deconstref = typename std::remove_const<deref<A>>::type;

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
        job(deconstref<A> _args);
        job(job<R,A> &&rhs);
        ~job() = default;

        // Get the return value
        R&& get_return_val();

        // Set the args for the function
        job<R,A>& set_args(deconstref<A> _args);

        // Return the arguments
        deconstref<A>& get_args();

        // Start the function
        void start(job_callee<R,A> func);
    protected:
    private:
        R return_val;
        deconstref<A> args;
};

// CONSTRUCTOR
template<typename R, typename A>
job<R,A>::job(deconstref<A> _args) :
    args(std::move(_args))
{
}

// MOVE CONSTRUCTOR
template<typename R, typename A>
job<R,A>::job(job<R,A> &&rhs) :
    args(std::move(rhs.args))
{
}

// Move the return value from this job
template<typename R, typename A>
R&& job<R,A>::get_return_val()
{
    return std::move(return_val);
}

// Move arguments into our arguments
template<typename R, typename A>
job<R,A>& job<R,A>::set_args(deconstref<A> _args)
{
    args = deref<A>(std::move(_args));
    return *this;
}

// Move our arguments out of this object if necessary
template<typename R, typename A>
deconstref<A>& job<R,A>::get_args()
{
    return std::move(args);
}

// Start the function
template<typename R, typename A>
void job<R,A>::start(job_callee<R,A> func)
{
    return_val = func(args);
}

#endif // SENTIMENTANALYSIS_PROTOTYPES_QUEUE_JOB_CPP
