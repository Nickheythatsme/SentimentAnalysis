#include "queue.cpp"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

class temp
{
    public:
        temp(int _x) : x(_x) {cout << "Constructor with arguments: " << x << endl;}
        temp() {cout << "Constructor: " << x << endl;}
        temp(const temp &rhs) {cout << "Copy constructor: " << rhs.x << endl; x = rhs.x;}
        temp(temp &&rhs) {cout << "Move constructor: " << rhs.x << endl; x = rhs.x; rhs.x = -1;}
        ~temp() {cout << "Destructor: " << x << endl;}
        int x {-1};
    private:
};

// Set current type easily
typedef temp c_type;

/*
 * Simple function to test job
 */
c_type simple_func(c_type s)
{
    cout << "c_type: " << s.x << endl;
    return s;
}


void test_queue()
{
    std::queue<c_type> jobs;

    for (int i=1; i < 2; ++i)
    {
        c_type c {i};
        jobs.push(std::move(c));
    }

    cout << endl << endl << endl << "Starting threads: " << endl;
    thread_queue<c_type, c_type> q1(simple_func, std::move(jobs), 4);
    q1.start_sync();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    test_queue();
    return 0;
}
