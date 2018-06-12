#include "config.hpp"
#ifndef SENTIMENTANALYSIS_TEST_GENERAL_H
#define SENTIMENTANALYSIS_TEST_GENERAL_H
#include <chrono>


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
        friend operator<<(std::ostream &out, const test_timer &rhs);
    protected:
    private:
        std::chrono::
};
