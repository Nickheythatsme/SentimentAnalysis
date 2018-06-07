#include "performance.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool func()
{
    return rand() % 5;
}

int main(int argc, char **argv)
{
    std::vector<size_t> sizes;
    for (int i=1; i < 100; ++i)
        sizes.emplace_back(i*10);
    std::vector<double> results;
    for (const auto &i : sizes)
    {
        results.emplace_back(i);
    }

    for (size_t i=0; i<100; ++i)
    {
        cout << i*10 << "\t" << results[i*10] << endl;
    }

    performance_result r(sizes, results);
    cout << r << endl;
}
