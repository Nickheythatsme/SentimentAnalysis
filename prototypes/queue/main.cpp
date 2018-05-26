#include <iostream>
#include <string>
#include "queue_base.h"
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

    job<c_type, const c_type&> j1 (simple_func, x);
    job<c_type, const c_type&> j2 (simple_func, std::move(x));

    j1.set_args(std::move(x));
    j1.set_args(y);

    j1.start();

    auto temp1 = j1.get_args();
    auto temp2 = std::move(j1.get_args());

    cout << "x: " << x << endl;

    return 0;
}
