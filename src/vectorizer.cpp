#include <iostream>
#include "parse.h"
#include "btree.hpp"
#include "text_package.h"

#ifdef __WIND32
#define DIR_DELIM '\\'
#else
#define DIR_DELIM '/'
#endif

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "usage: ./vectorize [text] [directories] [...]" << endl;
        exit(EXIT_SUCCESS);
    }

    // Make the text package
    text_package package;

    // Load text files from directories
    for (size_t i=1; i<argc; ++i)
    {
        string dir { argv[i] };

        // Append '*' or '/*' so that glob works
        if (DIR_DELIM != dir.back())
        {
            dir += DIR_DELIM;
        }
        if ('*' != dir.back())
        {
            dir += '*';
        }

        cout << "Reading files from: " << dir << endl;
        package.load_files(dir);
    }

    return 0;
}
