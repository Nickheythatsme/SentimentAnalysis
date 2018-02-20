#include "parse.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    std::ifstream fin(argv[1]);
    char buff[1024];

    fin.get(buff, 1024, '\n');
    for(uint i = 0; i < fin.gcount(); ++i)
    {
        cout << buff[i];
    }

    cout << "done" << endl;

    return 0;
}

