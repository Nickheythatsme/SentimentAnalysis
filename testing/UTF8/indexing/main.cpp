#include <iostream>
#include <cstdint>

using namespace std;

struct utf8_char
{
    utf8_char(const char *);
    int len(const char *);
    char one;
    char two;
    char three;
    char four;
};

int main(int argc, char **argv)
{
    cout << sizeof(utf8_char) << endl;
}

