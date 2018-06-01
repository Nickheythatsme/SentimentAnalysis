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

int main(int argc, char *argv[])
{
    matrix m;
    m.fill_random(1000,1000);
    std::queue<matrix> jobs;
    for (int i=0; i < 100; ++i)
        jobs.push(matrix(m));

    cout << "Starting test" << endl;
    for (int i=2; i < 15; ++i)
    {
        thread_queue<int, matrix&> q1 (&test_func, std::queue<matrix>(jobs), i);
        auto start = std::chrono::system_clock::now();
        q1.start_sync();
        auto end = std::chrono::system_clock::now();
        cout << "Processing time for " << i << " cores: " << (std::chrono::duration<double> {end-start}).count() << endl;
    }
    return 0;
}

