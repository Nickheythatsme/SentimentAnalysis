#include "class.h"

A::A() :
    data("no_data")
{
    cout << "\tConstructor called" << endl;
}

A::A(const A& a) :
    data(a.data)
{
    cout << "\tCopy Constructor called" << endl;
}

A::A(const string &_data) :
    data(_data)
{
    cout << "\tConstructor called" << endl;
}

A::A(A &&rhs) :
    data(std::move(rhs.data))
{
    cout << "\tMove Constructor called" << endl;
}

A::~A()
{
    cout << "\tDestructor called" << endl;
    data.clear();
}

std::ostream& operator<<(std::ostream &out, const A &obj)
{
    if (obj.data.empty())
        out << "no data";
    else 
        out << obj.data;
    return out;
}
