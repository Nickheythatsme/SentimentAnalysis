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
        T my_name;

};

template<typename T>
void base<T>::addAndCout(T &&name)
{
    cout << name << endl;
    my_name = std::forward<T>(name);
    names.emplace_back(std::forward<T>(name));
}

template<typename T>
void addAndCout(T &&name)
{
    cout << name << endl;
    cout << '\t' << typeid(name).name() << endl;
    cout << endl;
}


int main(int argc, char **argv)
{
    std::string name {"test1"};
    addAndCout(name);
    addAndCout("test2");
    addAndCout(std::string("test3"));


    base<std::string> b;
    b.addAndCout(std::move(name)); 
    cout << "After move: " << name << endl;
    b.addAndCout("test1");
    b.addAndCout(std::string("test2")); // 

    /*
    int i = 0;
    addAndCout(i);
    addAndCout(1);
    addAndCout(int(2));
    addAndCout(std::move(i));
    */
}

