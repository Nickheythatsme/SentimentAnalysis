#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
using std::cout;
using std::endl;

template<typename T>
class base
{
    public:
        void addAndCout(T &&name);
    private:
        std::vector<T> names;

};

template<typename T>
void base<T>::addAndCout(T &&name)
{
    cout << name << endl;
    names.emplace_back(std::forward<T>(name));
}

template<typename T>
void addAndCout(T &&name)
{
    cout << name << endl;
    cout << '\t' << typeid(name).name() << endl;
    cout << "\tint: " << std::is_same<T, int>::value << endl;
    cout << "\tint&: " << std::is_same<T, int&>::value << endl;
    cout << "\tint&&: " << std::is_same<T, int&&>::value << endl;
    cout << endl;
}


int main(int argc, char **argv)
{
    /*
    std::string name {"test1"};
    addAndCout(name);
    addAndCout("test2");
    addAndCout(std::string("test3"));


    base<std::string> b;
    b.addAndCout(name); // FAIL b/c name is not lvalue
    b.addAndCout("test1");
    b.addAndCout(std::string("test2")); // 
    */

    int i = 0;
    addAndCout(i);
    addAndCout(1);
    addAndCout(int(2));
    addAndCout(std::move(i));

}

