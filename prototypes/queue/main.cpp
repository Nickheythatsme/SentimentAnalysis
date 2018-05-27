#include <iostream>
#include <string>
#include <vector>
#include "job.hpp"
using namespace std;

// Set current type easily
typedef string c_type;

/*
 * Simple function to test job
 */
c_type simple_func(const c_type &s)
{
    cout << s << endl;
    return s;
}

int main()
{
    c_type x {'x'};
    c_type y {'y'};
    std::vector<c_type> v;
    v.emplace_back("test");
    v.emplace_back("test");

    job<c_type, const c_type&> j1 (simple_func, std::move(x));
    job<c_type, const c_type&> j2 (simple_func, y);

    j1.set_args(y);
    j1.set_args(std::move(y));
    j1.start();

    c_type ret = std::move(j1.get_return_val());


    return 0;
}
