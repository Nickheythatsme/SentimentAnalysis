#include "performance.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool func(size_t n)
{
    char array[n];
    for (size_t i=0; i<n; ++i)
        array[i] = char(rand());
    return true;
}

int main(int argc, char **argv)
{
    performance_test t("Performance test!", func, 10000, 1000000);
    try {
        t.start();
    }catch(test_err &e)
    {
        cout << e << endl;
    }

    cout << t.get_results() << endl;
}
