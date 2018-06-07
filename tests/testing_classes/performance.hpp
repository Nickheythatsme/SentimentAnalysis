/*
This class measures bigO performance of the object
*/
#include <chrono>
#include "config.hpp"
#include "result.hpp"

// Testing functions
template<typename T>
using test_function = bool (*)(O *obj, size_t n);

// A single data point used to measure the closeness of the equation
struct data_point
{
    std::chrono::high_resolution_clock value;
    size_t n;
};

// A results class that calculates the closeness O(n) equation
// example:
// O(n) equation
// 
// log(n)
// n: 0.81
// n*2: .98
// n*n: 0.91
class performace_result : public general_result 
{
};

// Conduct a performance test, return the result
template<typename T>
class performance_test : public config
{
    public:
        performance_test() = delete;
        performance_test(const performance_test &rhs);
        performance_test(performance_test &&rhs);
        ~performance_test() = default;

        general_result start();
    protected:
    private:
        test_function<T> func;
        general_result results;
};
