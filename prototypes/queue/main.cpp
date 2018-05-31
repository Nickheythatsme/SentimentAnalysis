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


int main()
{
    test_job();
    return 0;
}
