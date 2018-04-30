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
}

template<class T>
decltype(auto) func(T &&obj)
{
    cout << "\tIs lvalue? " << std::is_lvalue_reference<T>{} << endl;
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
        cout << endl << "***Passing const obj to non-const function with variable return type" << endl;
        const example e;
        func2(e);
    }


}
