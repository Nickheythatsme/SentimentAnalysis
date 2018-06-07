/*
This class measures bigO performance of the object
*/
#include <chrono>
#include <cmath>
#include "config.hpp"
#include "result.hpp"

// Testing functions
template<typename T>
using test_function = bool (*)(O *obj, size_t n);

// A single data point used to measure the closeness of the equation
struct data_point
{
    double y;
    size_t x;
};

// A results class that calculates the closeness (r^2) O(n) equation
// example:
// O(n) equation
// 
// log(n)
// n: 0.81
// n*2: .98
// n*n: 0.91
class performace_result : public general_result 
{
    public:
        performace_result() = default;
        performace_result(const performace_result &rhs);
        performace_result(performace_result &&rhs);
        ~performace_result();
        std::ostream& operator<<(std::ostream &out, const performace_result &rhs);
    protected:
        std::ostream& display(std::ostream &out);
    private:
        std::vector<data_point> calc_n(size_t count_x, size_t max_x);
        double correlation(const std::vector<data_point> &l1, const std::vector<data_point> &l2);
        std::vector<data_point> data_points;
};

// Output to a stream
std::ostream& performace_result::display(std::ostream &out)
{
    test_case::display(out);
    out << "Correlation: " << std::endl;
    return out;
}

// Calculate a line n and put the points into a vector
std::vector<data_point> performance_result::calc_n(size_t count_x, size_t max_x)
{
    std::vector<data_point> to_return {count_x};
    auto increment = max_x / count_x;
    size_t i = 0;
    for (auto &c : to_return)
    {
        c.y = i;
        c.x = i;
        i += increment;
    }
    return to_return;
}

// Calculate the Pearson R correlation
double performance_result::correlation(const std::vector<data_point> &l1, const std::vector<data_point> &l2)
{
    double part1 = 0.0;
    for ()
}

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
