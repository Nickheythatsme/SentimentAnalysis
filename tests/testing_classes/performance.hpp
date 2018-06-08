/*
This class measures bigO performance of the object
*/
#include <chrono>
#include <cmath>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include "config.hpp"
#include "result.hpp"

// Testing functions

using test_function = bool (*)(size_t n);

struct correlations
{
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
        performance_result();
        explicit performance_result(const std::vector<size_t> &_n_points, const std::vector<double> &_data_points);
        performance_result(const performance_result &rhs) = default;
        performance_result(performance_result &&rhs) = default;
        ~performance_result() = default;
        void calculate_results(const std::vector<size_t> &_n_points, const std::vector<double> &_data_points);
        friend std::ostream& operator<<(std::ostream &out, const performance_result &rhs);
    protected:
        std::ostream& display(std::ostream &out) const;
    private:
        // Calculate various O(n) equations to compare the correlation to the observed values
        static std::vector<double> calc_log_n(const std::vector<size_t> &n_points);
        static std::vector<double> calc_n_log_n(const std::vector<size_t> &n_points);
        static std::vector<double> calc_n(const std::vector<size_t> &n_points);
        static std::vector<double> calc_n2(const std::vector<size_t> &n_points);
        static std::vector<double> calc_two_to_n(const std::vector<size_t> &n_points);
        
        void run_correlations();
        static double calc_correlation(const std::vector<double> &l1, const std::vector<double> &l2);
        std::vector<double> data_points;
        std::vector<size_t> n_points;
        correlations correlation_result;
};

// CONSTRUCTOR
performance_result::performance_result() :
    general_result(),
    n_points(),
    correlation_result()
{
}
// CONSTRUCTOR
performance_result::performance_result(const std::vector<size_t> &_n_points, const std::vector<double> &_data_points) :
    general_result(),
    data_points(_data_points),
    n_points(_n_points),
    correlation_result()
{
    run_correlations();
}

// Manually run the correlation results
void performance_result::calculate_results(const std::vector<size_t> &_n_points, const std::vector<double> &_data_points)
{
    n_points = _n_points;
    data_points = _data_points;
    run_correlations();
}

// Output to a stream
std::ostream& performance_result::display(std::ostream &out) const
{
    general_result::display(out) << std::endl;
    out << "\tCorrelations: " << std::endl
        << "\t\tO(log(n)): " << correlation_result.log_n << endl
        << "\t\tO(nlog(n)): " << correlation_result.n_log_n << endl
        << "\t\tO(n): " << correlation_result.n << endl
        << "\t\tO(n^2): " << correlation_result.n2 << endl
        << "\t\tO(2^n): " << correlation_result.two_to_n;

    return out;
}

std::ostream& operator<<(std::ostream &out, const performance_result &rhs)
{
    return rhs.display(out);
}

// Calculate all the correlations and return them in a struct
void performance_result::run_correlations()
{
    std::vector<double> calculated;

    // Find O(log(n))
    calculated = calc_log_n(n_points);
    correlation_result.log_n = calc_correlation(data_points, calculated);

    // Find O(nlog(n))
    calculated = calc_n_log_n(n_points);
    correlation_result.n_log_n = calc_correlation(data_points, calculated);

    // Find O(n)
    calculated = calc_n(n_points);
    correlation_result.n = calc_correlation(data_points, calculated);

    // Find O(n^2)
    calculated = calc_n2(n_points);
    correlation_result.n2 = calc_correlation(data_points, calculated);

    // Find O(2^n)
    calculated = calc_two_to_n(n_points);
    correlation_result.two_to_n = calc_correlation(data_points, calculated);
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

// Calculate the Pearson R correlation. Returns R^2
double performance_result::calc_correlation(const std::vector<double> &l1, const std::vector<double> &l2)
{
    if (l1.size() != l2.size()) return -2;
    size_t n = l1.size();
    size_t iter = 1;

    long double sum_products = 0.0; // sum x * y
    long double sum_l1 = 0.0;       // sum x
    long double sum_l1_2 = 0.0;     // sum x^2
    long double sum_l2 = 0.0;       // sum y
    long double sum_l2_2 = 0.0;     // sum y^2

    for (size_t i=0; i<n-iter; i+=iter)
    {
        sum_products += l1[i] * l2[i];
        sum_l1 += l1[i];
        sum_l1_2 += l1[i] * l1[i];
        sum_l2 += l2[i];
        sum_l2_2 += l2[i] * l2[i];
    }

    long double top = (n*sum_products - (sum_l1)*(sum_l2));
    long double bottom = sqrt((n*sum_l1_2 - sum_l1*sum_l1) * (n*sum_l2_2 - sum_l2*sum_l2));
    return pow(top/bottom, 2.0l);
}

// Conduct a performance test, return the result
class performance_test : public config
{
    public:
        performance_test() = delete;
        performance_test(string name, test_function _func, size_t _iterations=1000, size_t _max=100);
        performance_test(const performance_test &rhs) = default;
        performance_test(performance_test &&rhs) = default;
        ~performance_test() = default;
        void start();
        const performance_result& get_result() {return results;}
    protected:
    private:
        void _start(std::atomic_bool &running);
        // Return the duration of time it took to execute that test
        double run_test(size_t current_size);
        void make_n_points(size_t iterations, size_t max);
        test_function func;
        performance_result results; 
        std::vector<size_t> n_points; // What values will we call the function to test?
        std::vector<double> test_results;
};

// CONSTRUCTOR
performance_test::performance_test(string name, test_function _func, size_t iterations, size_t max) :
    config(std::move(name)),
    func(_func),
    test_results(),
    results()
{
    make_n_points(iterations, max);
}

// Calculate y = m*x^2 and put those values into a vector. 
// This is to test more stuff at the low end (where it is fast and where results matter more).

void performance_test::make_n_points(size_t iterations, size_t max)
{
    // Find m for y = m*x^3
    double m = (double)max / (iterations*iterations*iterations);

    for (size_t i=1; i<iterations+1; ++i)
    {
        size_t val = m * i * i * i;
        n_points.emplace_back((val) ? val : 1); // We don't want 0 values (size 0 doesn't make sense)
    }
}

// Wrapper for the start. Displays the progess
void performance_test::start()
{
    logging logger(this->name, this->verbose);
    std::atomic_bool running {true};
    std::thread t(&performance_test::_start, this, std::ref(running));
    size_t total_iterations = n_points.size();
    while (running && total_iterations != results.iterations)
    {
        double percent = 100*((double) results.iterations/total_iterations);
        std::cout << "Running test..." 
                  << results.iterations << "/" << total_iterations << "\t"
                  << percent << "%" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    t.join();
}

// Start the test
void performance_test::_start(std::atomic_bool &running)
{
    results.name = this->name;
    results.beginning = std::chrono::system_clock::now();
    try{
        for (const auto &c : n_points)
        {
            test_results.emplace_back(run_test(c));
            results.iterations += 1;
        }
    }catch(test_err &e)
    {
        std::cerr << e << std::endl;
        running = false;
        return;
    }
    std::chrono::duration<double> average {0};
    std::chrono::duration<double> total {0};
    results.calculate_results(n_points, test_results);
    results.ending = std::chrono::system_clock::now();
    results.passed = true;
    running = false;
}

using namespace std::chrono;

double performance_test::run_test(size_t current_size)
{
    auto start = high_resolution_clock::now();
    bool fresult = func(current_size);
    if (!fresult)
        throw test_err("Performance test: call to function returned false. Error with function call.",this->name);
    auto end = high_resolution_clock::now();
    duration<double> exec_time = duration_cast<duration<double, std::micro>>(end - start);
    return exec_time.count();
}