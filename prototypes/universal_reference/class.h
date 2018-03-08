#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#ifndef CLASS_
#define CLASS_
class A
{
    public:
        A();
        A(const A& a);
        explicit A(const string &_data);
        A(A &&rhs);
        ~A();
        void setText(const string &obj) {data = obj;}
        friend std::ostream& operator<<(std::ostream &out, const A &obj);
    private:
        string data;
};

#endif //CLASS_



