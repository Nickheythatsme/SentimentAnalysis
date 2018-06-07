#include "case.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool func()
{
    return rand() % 5;
}

int main(int argc, char **argv)
{
    test_case c1 ("test", func);
    cout << c1.start() << endl;
}
