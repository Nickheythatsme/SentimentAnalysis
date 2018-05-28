#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace std;

mutex resource_mutex;
int value;

void init(int x)
{
    printf("Calling init %d\n", x);
    unique_lock<mutex> lk(resource_mutex);
    value = x;
    printf("\nInitializing %d\n", value);
    lk.unlock();
    usleep(1000000/2);
}

int main(int argc, char **argv)
{
    thread threads[10];
    int i=0;
    for (auto &t : threads)
        t = thread(init,i++);
    for (auto &t : threads) t.join();
    return 0;
}
