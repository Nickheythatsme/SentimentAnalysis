#include "test_case.h"

/* test_err implementation */
std::ostream& operator<<(std::ostream &out, const test_err &rhs)
{
    out << "Test Error: " << endl
        << "Name: " << rhs.name << endl
        << "Message: " << rhs.message << endl;
    return out;
}

/* test_result implementation */
// output to a stream
std::ostream& operator<<(std::ostream& out, const test_result &rhs)
{
    out << "Test name: " << rhs.name << endl
        << "\tPassed: " << rhs.passed << endl
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

/* configuration implementation */
// Constructors with arguments
template<class T, class D>
configuration<T,D>::configuration(custom_function<T,D> _func, const D &_data) :
    func(_func),
    data(_data),
    obj()
{
}

template<class T, class D>
configuration<T,D>::configuration(custom_function<T,D> _func, const D &_data, const T &_obj) :
    func(_func),
    data(_data),
    obj(_obj)
{
}

/* unit_test implementation */
// Constructors
template<class T, class D>
unit_test<T,D>::unit_test(custom_function<T,D> _func, const D &_data) :
    configuration<T,D>(_func, _data),
    result()
{
}

template<class T, class D>
unit_test<T,D>::unit_test(custom_function<T,D> _func, const D &_data, const T& _obj) :
    configuration<T,D>(_func, _data, _obj),
    result()
{
}

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
    result = test_result();

    try{
        for (int i=0; i < this->iterations; ++i)
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
    } catch(const test_err &err){
        std::cerr << err << endl;
        return result;
    }
    result.passed = true;
    result.average = result.total/result.iterations;
    result.name = this->name;
    return result;
}