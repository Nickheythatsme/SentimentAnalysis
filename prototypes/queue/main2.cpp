#include <iostream>
#include <vector>
#include <string>
using namespace std;

class movee
{
public:
    movee() = default;
    movee(movee && rhs)
    {
        cout << "movee moving!" << endl;
        data = rhs.data;
        rhs.data = 0;
    }
    movee(const movee & rhs)
    {
        cout << "movee copying!" << endl;
        data = rhs.data;
    }
    ~movee() = default;
    movee& operator=(const movee & m)
    {
        cout << "Assigning m" << endl;
        data = m.data;
    }
    movee& operator=(movee && m)
    {
        cout << "Move assigning m" << endl;
        data = m.data;
        m.data = 0;
    }
    int data;
private:
protected:
};

template<class T, class X>
class example
{
    public:
        example() = default;
        example(T &&_m) {m = std::forward<T>(_m);}
        example(const example<T,X>&) = default;
        example(example<T,X> &&rhs) = default;
        ~example() = default;
        void set_args(T &&_m)
        {
            m = std::forward<T>(_m); 
        }

        T m;
    protected:
    private:
};

template<class T>
void test_func(T &&a)
{
    T b = std::forward<T>(a);
}

int main(int argc, char **argv)
{
    string s1 {"Hello"};
    /*
    example<string,int> e1(std::move(s1));
    cout << s1 << endl;
    e1.set_args(s1);
    e1.set_args(std::move(s1));
    */

    test_func(s1);
    cout << s1 << endl;
    test_func(std::move(s1));
    cout << s1 << endl;

    return 0;
}
