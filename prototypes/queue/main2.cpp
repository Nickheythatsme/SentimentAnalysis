#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

using std::cout;
using std::endl;
using std::cin;



std::queue<int> data_queue;
std::mutex mut;
std::condition_variable data_cond;

int add_data()
{
    for (int i =0; i<4; ++i)
    {
        auto c = i;
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(c);
        data_cond.notify_one();
    }
}

int process_data()
{
    while(true)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(
                lk, []{return !data_queue.empty();});
        cout << "Popping: " << data_queue.front() << endl;
        data_queue.pop();
        lk.unlock();
        cout << "Waiting..." << endl;
    }
}

int main(int argc, char **argv)
{
    std::thread process_d (process_data);
    process_d.detach();
    cin.ignore(100,'\n');
    add_data();
    cin.ignore(100,'\n');
    add_data();
    cin.ignore(100,'\n');

    return 0;
}
