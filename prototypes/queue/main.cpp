#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "job.hpp"
#include "worker.hpp"
using namespace std;

// Set current type easily
typedef int c_type;

/*
 * Simple function to test job
 */
c_type simple_func(const c_type &s)
{
    cout << s << endl;
    return s;
}

void test_job()
{
    c_type x {'x'};
    c_type y {'y'};

    job<c_type, const c_type&> j1 (simple_func, std::move(x));
    job<c_type, const c_type&> j2 (simple_func, y);

    j1.set_args(y);
    j1.set_args(std::move(y));
    j1.start();

    c_type ret = std::move(j1.get_return_val());
}

void test_worker()
{
    std::mutex mut;
    c_type x {'x'};

    std::queue<job<c_type,const c_type&>> jobs;
    jobs.push(job<c_type,const c_type&>(simple_func, c_type(x)));
    worker<c_type, const c_type&> w1 (mut, jobs);

    std::thread t(&worker<c_type, const c_type&>::start_working, std::ref(w1));
    t.join();
}

int main()
{
    test_worker();
    return 0;
}
