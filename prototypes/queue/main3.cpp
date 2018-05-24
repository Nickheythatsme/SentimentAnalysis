#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;

template<typename T>
void addAndCout(T &&name)
{
    std::vector<T> v;

    cout << name << endl;
}

int main(int argc, char **argv)
{
    std::string name {"test"};

    addAndCout(std::string("rvalue")); // FINE      move rvalue instead of copying it
    addAndCout("New string");          // ERROR     make a new string instead of copying
    //addAndCout(name);                  // ERROR     copy lvalue
}

