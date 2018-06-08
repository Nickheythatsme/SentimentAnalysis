#include "../testing_classes/case.hpp"
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
        thread_queue<int, matrix&> tq (test_func, std::vector<matrix>(jobs), a);
        tq.start();
    }

    return true;
}

int main(int argc, char *argv[])
{
    test_case case1 ("multi threaded queue test on various threads", run_test);
    case1.start();
    cout << case1.get_result() << endl;


    return !(case1.get_result().passed);
}

