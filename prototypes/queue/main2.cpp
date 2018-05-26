#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <stdio.h>

using std::cout;
using std::endl;
using std::cin;

std::queue<int> data_queue;
std::mutex mut;
std::condition_variable data_cond;

int add_data()
{
    for (int i =0; i<1000; ++i)
    {
        auto c = i;
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(c);
        // data_cond.notify_one();
        data_cond.notify_all();
    }
}

int process_data(int x)
{
    while(true)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(
                lk, []{return !data_queue.empty();});
        printf("Thread %d popping: %d\n", x, data_queue.front());
        data_queue.pop();
        lk.unlock();
        printf("Thread %d waiting...\n", x);
    }
}

int main(int argc, char **argv)
{
    for (int i=0; i < 10; ++i)
    {
        std::thread process_d (process_data, i);
        process_d.detach();
    }

    cin.ignore(100,'\n');
    add_data();
    cin.ignore(100,'\n');
    add_data();
    cin.ignore(100,'\n');

    return 0;
}
