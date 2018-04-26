#include "test_case.h"

/* test_result implementation */
// output to a stream
std::ostream& operator<<(std::ostream& out, const test_result &rhs)
{
    out << "Test name: " << rhs.name << endl
        << "Passed: " << rhs.passed << endl
        << "\tIterations completed: " << rhs.iterations << endl
        << "\tAverage exec time: " << rhs.display_time(rhs.average) << endl
        << "\tTotal exec time:   " << rhs.display_time(rhs.total);
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
    to_ret.append(std::to_string(microseconds) + "ms ");

    return to_ret;
}

/* unit_test implementation */
// Constructors
template<class T, class D>
unit_test<T,D>::unit_test(custom_function<T,D> _func, const D &_data) :
    func(_func),
    data(_data),
    obj(),
    config()
{
}

template<class T, class D>
unit_test<T,D>::unit_test(custom_function<T,D> _func, const D &_data, const T& _obj) :
    func(_func),
    data(_data),
    obj(_obj),
    config()
{
}

template<class T, class D>
unit_test<T,D>::unit_test(const custom_function<T,D> _func, const D &_data, const configuration &_config) :
    func(_func),
    data(_data),
    obj(),
    config(_config)
{
}

template<class T, class D>
unit_test<T,D>::unit_test(const custom_function<T,D> _func, const D &_data, const T &_obj, const configuration &_config) :
    func(_func),
    data(_data),
    obj(_obj),
    config(_config)
{
}

// Commence one test. 
// RETURNS the duration difference between end/start
// THROWS test_err if a test failed
template<class T, class D>
decltype(auto) unit_test<T,D>::commence_test()
{
    auto start = std::chrono::steady_clock::now();
    bool passed = func(obj, data);
    auto end = std::chrono::steady_clock::now();
    if (!passed)
        throw test_err("Test failed", name);
    return end - start;
}

// Start the commence_test function for x number of times. Record all times and calculate the average
template<class T, class D>
test_result unit_test<T,D>::start()
{
    test_result result;

    try{
        for (int i=0; i < config.iterations; ++i)
        {
            result.total += commence_test();
            ++result.iterations;
        }
    }catch(const test_err &err){
        std::cerr << "Testing error: " << err.name << ": " << err.message << endl;
        return result;
    }
    result.passed = true;
    result.average = result.total/result.iterations;
    result.name = name;
    return result;
}