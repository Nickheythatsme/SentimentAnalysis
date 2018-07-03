#include <iostream>
#include "parse.h"
#include "btree.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "usage: ./vectorize [text] [files] [...]" << endl;
        exit(EXIT_SUCCESS);
    }

    return 0;
}
