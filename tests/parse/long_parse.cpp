#include <fstream>
#include <iostream>
#include <string>
#include "../test_case.h"
#include "../text_package.h"
#include "parse.h"

using std::cout;
using std::endl;

bool test_long(parse &parser, text_package &p)
{
    for (auto const &text : p)
        parser(text);
    return true;
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        try {
            cout << "Opening file: " << argv[1] << endl;
            auto package = text_package(argv[1]);
            unit_test<parse, text_package> unit(test_long, package);
            unit.set_iterations(100);
            unit.set_name("long parse");
            unit.set_verbose(true);
            auto result =  unit.start();
            if (result.passed)
                cout << result << endl;
        }
        catch(const text_package_error &err) {
            cerr << err << endl;
        }
    }
    else
        cout << "Unable to perform long test (no directory given)" << endl;

    return 0;
}
