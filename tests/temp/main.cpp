#include "../test_case.h"
#include <vector>

using namespace std;

bool test_func(vector<int>& x, vector<int>& y)
{
    for (auto const &i : y)
    {
        cout << i << " ";
        x.emplace_back(i);
    }
    cout << endl;
    return true;
}

int main(int argc, char *argv[])
{
    configuration config;
    config.iterations = 100;
    //unit_test<vector<int>, vector<int>> unit(test_func, {1,2,3,4,5}, config);
    unit_test<vector<int>, vector<int>> unit(test_func, {1,2,3,4,5});
    unit.start();
}
