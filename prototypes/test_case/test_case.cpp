#include "test_case.h"

/* test_err implementation */
std::ostream& operator<<(std::ostream &out, const test_err &rhs)
{
    out << "Test Error: " << endl
        << "\tName: " << rhs.name << endl
        << "\tMessage: " << rhs.message << endl;
    return out;
}

/* test_result implementation */
// output to a stream
std::ostream& operator<<(std::ostream& out, const test_result &rhs)
{
    out << "Test name: " << rhs.name << endl
        << "\tStarted:\t" << ((rhs.started) ? "true" : "false") << endl
        << "\tPassed: \t" << ((rhs.passed) ? "true" : "false") << endl
        << "\tIterations completed:\t" << rhs.iterations << endl
        << "\tAverage exec time:\t" << rhs.display_time(rhs.average) << endl
        << "\tTotal exec time:\t" << rhs.display_time(rhs.total);
    return out;
}

// format the time and return it as a string
string test_result::display_time(const std::chrono::duration<double> &t)
{
    // Find the integer value of each hour/min/sec/etc
    auto hours = std::chrono::duration_cast<std::chrono::hours>(t).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(t).count() % 60;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(t).count() % 60;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t).count() % 1000; 
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t).count() % 1000;
    string to_ret;

    if (hours < 10) to_ret.append("0");
    to_ret.append(std::to_string(hours) + ":");

    if (minutes < 10) to_ret.append("0");
    to_ret.append(std::to_string(minutes) + ":");

    if (seconds < 10) to_ret.append("0"); 
    to_ret.append(std::to_string(seconds) + " ");

    to_ret.append(std::to_string(milliseconds) + "ms ");
    to_ret.append(std::to_string(microseconds) + "us ");

    return to_ret;
}

/* base configuration implementation */
// Constructor with arguments
base_config::base_config(const string &_name, bool _verbose, bool _copy_data, size_t _iterations) :
    name(_name),
    verbose(_verbose),
    copy_data(_copy_data),
    iterations(_iterations)
{
}

// Assign the values in this base_config to equal another base_config
base_config& base_config::operator=(const base_config &rhs)
{
    name = rhs.name;
    verbose = rhs.verbose;
    copy_data = rhs.copy_data;
    iterations = rhs.iterations;

    return *this;
}

/* configuration implementation */
// Constructors with arguments
template<class T, class D>
configuration<T,D>::configuration(custom_function<T,D> _func, const T &_obj, const D &_data) :
    base_config(),
    func(_func),
    data(_data),
    obj(_obj)
{
}

// Constructor with objects being moved
template<class T, class D>
configuration<T,D>::configuration(custom_function<T,D> _func, T &&_obj, D &&_data) :
    base_config(),
    func(_func),
    data(std::move(_data)),
    obj(std::move(_obj))
{}

/* unit_test implementation */
// Constructors
template<class T, class D>
unit_test<T,D>::unit_test(custom_function<T,D> _func, const T& _obj, const D &_data) :
    configuration<T,D>(_func, _obj, _data),
    result(this->name)
{}

// Constructor with objects being moved
template<class T, class D>
unit_test<T,D>::unit_test(custom_function<T,D> _func,  T&& _obj,  D&& _data) :
    configuration<T,D>(_func, std::move(_obj), std::move(_data)),
    result(this->name)
{}

// Commence one test.
// RETURNS the duration difference between end/start
// THROWS test_err if a test failed
template<class T, class D>
decltype(auto) unit_test<T,D>::commence_test(T &obj, D &data)
{
    auto start = std::chrono::steady_clock::now();
    bool passed = this->func(this->obj, this->data);
    auto end = std::chrono::steady_clock::now();
    if (!passed)
        throw test_err("Test failed", this->name);
    return end - start;
}

// Start the commence_test function for x number of times. Record all times and calculate the average
template<class T, class D>
test_result unit_test<T,D>::start()
{
    result = test_result(this->name);
    result.started = true;

    // Try to catch exceptions
    try{
        for (size_t i=0; i < this->iterations; ++i)
        {
            if (this->copy_data)
            {
                T obj_copy(this->obj);
                D data_copy(this->data);
                result.total += commence_test(obj_copy, data_copy);
            }
            else
                result.total += commence_test(this->obj, this->data);
            ++result.iterations;
        }
        // Catch and display test_err
    } catch(const test_err &err)
    {
        std::cerr << err << endl;
        return result;
        // Catch and display generic error
    }catch(...)
    {
        std::cerr << "Unknown error" << endl;
        return result;
    }

    result.passed = true;
    result.average = result.total/result.iterations;
    return result;
}