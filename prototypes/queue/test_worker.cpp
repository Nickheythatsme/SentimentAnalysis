#include "worker.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;

char test_func(const std::string &s)
{
    cout << s << endl;
    return s[0];
}

int test_worker()
{
    // Make queue and arguments
    std::string base {"A"};
    std::queue<job<char, const std::string&>> jobs;

    for (int i=0; i < 10; ++i)
    {
        job<char, const std::string&> a_job(test_func, base);
        jobs.push(std::move(a_job));
        ++base[0];
        if (base[0] > 'z')
            base[0] = 'A';
    }

    // Make worker variables
    std::mutex jobs_mut;
    std::mutex rets_mut;
    std::condition_variable data_cond;

    // Make worker queue and return value vector
    std::vector<char> rets;

    worker<char, const std::string&> w1 (jobs_mut, jobs, rets_mut, rets, data_cond);
    std::thread t(&worker<char, const std::string&>::start_working, std::ref(w1));
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Get lock
    std::unique_lock<std::mutex> jobs_lock(jobs_mut);

    // Change condition
    jobs_lock.unlock();

    // Call notify
    data_cond.notify_one();
    cout << "MAIN: waiting to join..." << endl;

    t.join();

    for (auto &c : rets)
        cout << c << endl;

    return 1;

}

int main()
{
    test_worker();
}
