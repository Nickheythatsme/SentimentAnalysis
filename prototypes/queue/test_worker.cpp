#include "worker.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

char test_func(std::string &s)
{
    for (int i=0; i < 10000; ++i)
        s += 'A';
    return s[0];
}

int test_worker()
{
    // Make queue and arguments
    std::string base {"A"};
    std::queue<job<char, std::string&>> jobs;

    for (int i=0; i < 3; ++i)
    {
        job<char, std::string&> a_job(test_func, base);
        jobs.push(std::move(a_job));
        ++base[0] = (base[0] > 'z') ? 'A' : base[0];
    }

    // Make worker variables
    std::mutex jobs_mut;
    std::mutex rets_mut;
    std::condition_variable data_cond;

    // Make worker queue and return value vector
    std::vector<job<char, std::string&>> rets;

    worker<char, std::string&> w1 (jobs_mut, jobs, rets_mut, rets, data_cond);
    std::thread t(&worker<char, std::string&>::start_working, std::ref(w1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Get lock
    std::unique_lock<std::mutex> jobs_lock(jobs_mut);
    w1.stop_working();

    // Change condition
    jobs_lock.unlock();

    // Call notify
    cout << "MAIN: notifying..." << endl;
    data_cond.notify_one();
    cout << "MAIN: waiting to join..." << endl;

    w1.working = true;
    t.join();

    for (auto &c : rets)
        cout << c.get_args()[0] << endl;

    return 1;
}

int main()
{
    test_worker();
}
