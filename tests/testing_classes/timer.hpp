#ifndef SENTIMENTANALYSIS_TEST_TIMER
#define SENTIMENTANALYSIS_TEST_TIMER

#include <chrono>
#include <ctime>
#include "config.hpp"

using namespace std::chrono;

class test_timer : public config
{
    public:
        test_timer();
        test_timer(std::string name);
        test_timer(const test_timer &rhs) = default;
        test_timer(test_timer &&rhs) = default;
        ~test_timer() = default;
        test_timer& start();
        test_timer& end();
        friend std::ostream& operator<<(std::ostream &out, const test_timer &rhs);
    protected:
    private:
        std::ostream& to_stream(std::ostream &out) const;

        high_resolution_clock::time_point start_time;
        high_resolution_clock::time_point end_time;
};

test_timer::test_timer() :
    config("timer")
{ }

test_timer::test_timer(std::string name) :
    config("timer")
{ }

test_timer& test_timer::start()
{
    start_time = high_resolution_clock::now();
    return *this;
}

test_timer& test_timer::end()
{
    end_time = high_resolution_clock::now();
    return *this;
}

std::ostream& test_timer::to_stream(std::ostream &out) const
{
    time_t start_ctime = system_clock::to_time_t(start_time);
    time_t end_ctime = system_clock::to_time_t(end_time);
    auto time_span = duration<double, std::milli>(end_time - start_time);

    out << "\tStart: " <<  ctime(&start_ctime)
        << "\tEnd: " << ctime(&end_ctime)
        << "\tDuration: " << time_span.count() << " ms";

    return out;
}


std::ostream& operator<<(std::ostream &out, const test_timer &rhs)
{
    return rhs.to_stream(out);
}

#endif // SENTIMENTANALYSIS_TEST_TIMER
