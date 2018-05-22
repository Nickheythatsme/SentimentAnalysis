#include <fstream>
#include <iostream>
#include <string>
#include "../test_case.h"
#include "../text_package.h"
#include "parse.h"

using namespace std;

bool test_simple(parse &parser, nullptr_t &t)
{
    parser("testing! this is a test");
    auto len = (parser.size() >= 5) ? 5 : parser.size() - 1;

    cout << "words parsed: " << parser.size() << endl;
    cout << "First " << len << " words: " << endl;
    for(int i=0; i < len; ++i)
    {
        cout << '"' << parser[i] << '"' << endl;
    }
    return parser.size() == 5;
}

bool test_long(parse &parser, text_package &p)
{
    for (auto const &text : p)
        parser(text);
    return true;
}

int main(int argc, char *argv[])
{
    unit_test<parse, decltype(nullptr)> unit(test_simple, nullptr);
    unit.set_name("test simple");
    auto result =  unit.start();
    if (result.passed)
        cout << result << endl;

    if (argc == 2)
    {
        try {
            auto package = text_package(argv[1]);
            cout << "Reading: " << package.size() << " files" << endl;
            unit_test<parse, text_package> unit2(test_long, package);
            unit2.set_iterations(100);
            unit2.set_name("long parse");
            auto result2 =  unit2.start();
            if (result2.passed)
                cout << result2 << endl;
        }
        catch(const text_package_error &err) {
            cerr << err << endl;
        }
    }
    else
        cout << "Unable to perform long test (no directory given)" << endl;
    return 0;
}

