#include "parse.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

using std::cout;
using std::endl;

void show_hex(char *s, int len)
{
    char c;
    for(uint i = 0; i < len; ++i)
    {
        c = s[i];
        printf("%x ", c);
        if( c == 0x27 )
        {
            printf("That's it!\n");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    std::ifstream fin(argv[1]);
    char buff[1024];

    fin.get(buff, 1024, '\n');
    fin.ignore(1024, '\n');

    while( !fin.eof() )
    {
        cout << buff << endl;
        show_hex(buff, strlen(buff));

        fin.get(buff, 1024, '\n');
        fin.ignore(1024, '\n');
    }

    return 0;
}

