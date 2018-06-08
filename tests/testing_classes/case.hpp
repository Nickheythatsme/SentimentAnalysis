/*
Nicholas Grout 6/6/2018
This class starts a test case, returning only true/false and timing the duration.
*/
#ifndef SENTIMENT_ANALYSIS_TEST_CASE
#define SENTIMENT_ANALYSIS_TEST_CASE

#include "config.hpp"
#include "result.hpp"

using testing_func = bool (*)();

class test_case : public config
{
    public:
        test_case() = delete;
        test_case(string name, testing_func _func);
        test_case(const test_case &rhs) = default;
        test_case(test_case &&rhs) = default;
        virtual ~test_case() = default;
        virtual void start();
        const general_result& get_result() {return results;}
    protected:
        testing_func func;
        general_result results;
};

// CONSTRUCTOR
test_case::test_case(string name, testing_func _func) :
    config(std::move(name)),
    func(_func),
    results()
{ }

// Run the test case;
void test_case::start()
{
    results = general_result();
    results.beginning = system_clock::now();
    results.name = this->name;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0; i < this->iterations; ++i)
    {
        ++results.iterations;
        results.iterations += func(); // increment test_result
    }
    auto end = std::chrono::high_resolution_clock::now();
    results.ending = system_clock::now();

    results.passed = results.iterations = this->iterations;
    results.average = (end - start) / results.iterations;
    results.total = end - start;
}

#endif // SENTIMENT_ANALYSIS_TEST_CASE
