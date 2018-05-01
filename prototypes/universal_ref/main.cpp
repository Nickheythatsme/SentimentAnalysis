#include <stdlib.h>
#include <iostream>

using namespace std;

class example
{
    public:
        example() {cout << "Constructor" << endl;}
        example(const example &obj) {cout << "Copy constructor" << endl;}
        example(example &&obj){cout << "Move constructor" << endl;}
        ~example(){cout << "Destructor" << endl;}
        int x;
};

template<class T>
decltype(auto) func(T &&obj)
{
    cout << "\tIs lvalue? " << std::is_lvalue_reference<decltype(obj)>{} << endl;
    return obj;
}

template<class T>
decltype(auto) func_const_obj(const T& obj)
{
    cout << "\tIs lvalue? " << std::is_lvalue_reference<decltype(obj)>{} << endl;
    return obj;
}


int main(int argc, char *argv[])
{
    {
        cout << "****lvalue reference to example object" << endl;
        example e;
        func(e);
    }

    {
        cout << endl << "****rvalue reference to an example object" << endl;
        example e;
        func(std::move(e));
        func(example());
    }

    {
        cout << endl << "****Forward reference (universal reference) to example object" << endl;
        auto c = std::forward<example>(example());
        func(c);
    }
    {
        cout << endl << "****Passing const obj and rvalue to const T& obj" << endl;
        const example e;
        func_const_obj(e);
        const example catcher2 = func_const_obj(example());
    }
}
