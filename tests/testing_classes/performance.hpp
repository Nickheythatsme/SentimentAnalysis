/*
This class measures bigO performance of the object
*/
#include <chrono>
#include <cmath>
#include <vector>
#include <iostream>
#include "config.hpp"
#include "result.hpp"

// Testing functions
template<typename T>
using test_function = bool (*)(T *obj, size_t n);

struct correlations
{
    double one;
    double log_n;
    double n_log_n;
    double n;
    double n2;
    double two_to_n;
};

// A results class that calculates the closeness (r^2) O(n) equation
// example:
// O(n) equation
// 
// log(n)
// n: 0.81
// n*2: .98
// n*n: 0.91
class performance_result : public general_result 
{
    public:
        performance_result() = delete;
        explicit performance_result(const std::vector<size_t> &_n_points, const std::vector<double> &_data_points);
        performance_result(const performance_result &rhs) = default;
        performance_result(performance_result &&rhs) = default;
        ~performance_result() = default;
        friend std::ostream& operator<<(std::ostream &out, const performance_result &rhs);
    protected:
        std::ostream& display(std::ostream &out) const;
    private:
        // Calculate various O(n) equations to compare the correlation to the observed values
        static std::vector<double> calc_1(const std::vector<size_t> &n_points);
        static std::vector<double> calc_log_n(const std::vector<size_t> &n_points);
        static std::vector<double> calc_n_log_n(const std::vector<size_t> &n_points);
        static std::vector<double> calc_n(const std::vector<size_t> &n_points);
        static std::vector<double> calc_n2(const std::vector<size_t> &n_points);
        static std::vector<double> calc_two_to_n(const std::vector<size_t> &n_points);
        
        correlations run_correlations() const;
        static double calc_correlation(const std::vector<double> &l1, const std::vector<double> &l2);
        std::vector<double> data_points;
        std::vector<size_t> n_points;
};

// CONSTRUCTOR
performance_result::performance_result(const std::vector<size_t> &_n_points, const std::vector<double> &_data_points) :
    general_result(),
    data_points(_data_points),
    n_points(_n_points)
{
}

// Output to a stream
std::ostream& performance_result::display(std::ostream &out) const
{
    general_result::display(out) << std::endl;
    auto correlation = run_correlations();
    out << "\tCorrelations: " << std::endl
        << "\t\tO(1): " << correlation.one << endl
        << "\t\tO(log(n)): " << correlation.log_n << endl
        << "\t\tO(nlog(n)): " << correlation.n_log_n << endl
        << "\t\tO(n): " << correlation.n << endl
        << "\t\tO(n^2): " << correlation.n2 << endl
        << "\t\tO(2^n): " << correlation.two_to_n;

    return out;
}

std::ostream& operator<<(std::ostream &out, const performance_result &rhs)
{
    return rhs.display(out);
}

// Calculate all the correlations and return them in a struct
correlations performance_result::run_correlations() const
{
    correlations to_find;
    std::vector<double> calculated;

    // Find O(1)
    calculated = calc_1(n_points);
    to_find.one = calc_correlation(data_points, calculated);

    // Find O(log(n))
    calculated = calc_log_n(n_points);
    to_find.log_n = calc_correlation(data_points, calculated);

    // Find O(nlog(n))
    calculated = calc_n_log_n(n_points);
    to_find.n_log_n = calc_correlation(data_points, calculated);

    // Find O(n)
    calculated = calc_n(n_points);
    to_find.n = calc_correlation(data_points, calculated);

    // Find O(n^2)
    calculated = calc_n2(n_points);
    to_find.n2 = calc_correlation(data_points, calculated);

    // Find O(2^n)
    calculated = calc_two_to_n(n_points);
    to_find.two_to_n = calc_correlation(data_points, calculated);

    return to_find;
}

// Calculate a line O(1) and put points into a vector
std::vector<double> performance_result::calc_1(const std::vector<size_t> &n_points)
{
    std::vector<double> to_return(n_points.size());
    for (int i=0; i<n_points.size(); ++i)
        to_return[i] = 1;
    return to_return;
}

// Calculate O(log(n))
std::vector<double> performance_result::calc_log_n(const std::vector<size_t> &n_points)
{
    std::vector<double> to_return(n_points.size());
    for (int i=0; i<n_points.size(); ++i)
        to_return[i] = log(n_points[i]);
    return to_return;
}

// Calculate O(n*log(n))
std::vector<double> performance_result::calc_n_log_n(const std::vector<size_t> &n_points)
{
    std::vector<double> to_return(n_points.size());
    for (int i=0; i<n_points.size(); ++i)
        to_return[i] = n_points[i] * log(n_points[i]);
    return to_return;
}

// Calculate a line O(n) and put the points into a vector
std::vector<double> performance_result::calc_n(const std::vector<size_t> &n_points)
{
    std::vector<double> to_return(n_points.size());
    for (int i=0; i<n_points.size(); ++i)
        to_return[i] = n_points[i];
    return to_return;
}

std::vector<double> performance_result::calc_n2(const std::vector<size_t> &n_points)
{
    std::vector<double> to_return(n_points.size());
    for (int i=0; i<n_points.size(); ++i)
        to_return[i] = n_points[i] * n_points[i];
    return to_return;
}

std::vector<double> performance_result::calc_two_to_n(const std::vector<size_t> &n_points)
{
    std::vector<double> to_return(n_points.size());
    for (int i=0; i<n_points.size(); ++i)
        to_return[i] = pow(2,n_points[i]);
    return to_return;
}


// Calculate the Pearson R correlation
double performance_result::calc_correlation(const std::vector<double> &l1, const std::vector<double> &l2)
{
    if (l1.size() != l2.size()) return -2;
    double l1_average = 0.0;
    double l2_average = 0.0;

    for (size_t i=0; i<l1.size(); ++i)
    {
        l1_average += l1[i];
        l2_average += l2[i];
    }
    l1_average /= l1.size();
    l2_average /= l1.size();

    double top = 0.0;

    for (size_t i=0; i<l1.size(); ++i)
    {
        top += (l1[i] - l1_average) * (l2[i] - l2_average);
    }

    // Calculate the bottom
    double l1_variance = 0.0;
    double l2_variance = 0.0;
    for (size_t i=0; i<l1.size(); ++i)
    {
        l1_variance += (l1[i] - l1_average) * (l1[i] - l1_average);
        l2_variance += (l2[i] - l2_average) * (l2[i] - l2_average);
    }
    double bottom = sqrt(l1_variance) * sqrt(l2_variance);

    return top / bottom;
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
