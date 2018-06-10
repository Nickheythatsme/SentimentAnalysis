#include "../testing_classes/case.hpp"
#include "../testing_classes/performance.hpp"
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

bool run_test()
{
    std::vector<int> args {0,1,2,3,4,8,12,16,20,80};
    matrix m;
    m.fill_random(1000, 1000);
    std::vector<matrix> jobs;
    for (int i=0; i < 100; ++i)
        jobs.push_back(matrix(m));

    for (const auto &a : args)
    {
        cout << "Starting thread queue with " << a << " threads" << endl;
        thread_queue<int, matrix&> tq (test_func, std::vector<matrix>(jobs), a);
        tq.start();
    }

    return true;
}

bool performance_func(size_t n)
{
    matrix m;
    m.fill_random(1000, 1000);
    std::vector<matrix> jobs;
    for (int i=0; i < 100; ++i)
        jobs.push_back(matrix(m));

    cout << "Starting thread queue with " << n << " threads" << endl;
    thread_queue<int, matrix&> tq (test_func, std::vector<matrix>(jobs), n);
    tq.start();

    return true;
}

int main(int argc, char *argv[])
{
    test_case case1 ("multi threaded queue test on various threads", run_test);
    // case1.start();
    // cout << case1.get_result() << endl;

    performance_test perf1("performance test of queue", performance_func, 10, 80); 
    perf1.start();
    cout << perf1.get_result() << endl;


    return !(case1.get_result().passed);
}

