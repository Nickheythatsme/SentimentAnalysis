#include "worker.cpp"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

// Set current type easily
typedef int c_type;

/*
 * Simple function to test job
 */
c_type simple_func(const c_type &s)
{
    cout << "c_type: " << s << endl;
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
    c_type x {'x'};
    std::mutex jobs_mut;
    std::mutex rets_mut;
    std::condition_variable data_cond;

    std::vector<c_type> rets;
    std::queue<job<c_type,const c_type&>> jobs;

    jobs.push(job<c_type,const c_type&>(simple_func, c_type(x)));
    worker<c_type, const c_type&> w1 (jobs_mut, jobs, rets_mut, rets, data_cond);

    // Start a new thread for our worker
    std::thread t(&worker<c_type, const c_type&>::start_working, std::ref(w1));
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Let our worker get started
    w1.stop_working();

    std::unique_lock<std::mutex> jobs_lock(jobs_mut);
    jobs.push(job<c_type,const c_type&>(simple_func, c_type(x)));
    jobs_lock.unlock();

    cout << "MAIN: notifying" << endl;
    data_cond.notify_one();

    cout << "jobs.empty() == " << jobs.empty() << endl;
    cout << "MAIN: waiting to join threads..." << endl;
    t.join();
}

int main()
{
    test_worker();
    return 0;
}
