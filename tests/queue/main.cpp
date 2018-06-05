#include "../test_case.h"
#include "tqueue.hpp"
#include "matrix.h"
#include <iostream>

using namespace std;

int test_func(matrix& m)
{
    for (int i=0; i<10; ++i)
        m *= 100.5;
    return 1;
}

bool run_test(int &num, nullptr_t &t)
{
    matrix m;
    m.fill_random(1000,1000);
    std::vector<matrix> jobs;
    for (int i=0; i < 100; ++i)
        jobs.push_back(matrix(m));

    thread_queue<int, matrix&> tq (test_func, std::move(jobs), num);
    tq.start();

    return true;
}

int main(int argc, char *argv[])
{
    std::vector<int> args {0,1,2,3,4,8,12,16,20,80};
    for (auto &v : args)
    {
        unit_test<int, nullptr_t> t1(run_test, nullptr, v);
        t1.set_name(to_string(v) + " core test");
        t1.set_verbose(true);
        cout << t1.start() << endl;
    }


    return 0;
}

