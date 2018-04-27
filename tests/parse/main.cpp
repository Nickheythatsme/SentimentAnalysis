#include <fstream>
#include <iostream>
#include <string>
#include "../test_case.h"
#include "../text_package.h"
#include "parse.h"

using namespace std;

bool test_simple(parse &parser, string &text)
{
    parser(text);
    auto len = (parser.size() >= 5) ? 5 : parser.size() - 1;

    cout << "words parsed: " << parser.size() << endl;
    cout << "First " << len << " words: " << endl;
    for(int i=0; i < len; ++i)
    {
        cout << '"' << parser[i] << '"' << endl;
    }
    return parser.size() > 0;
}

bool test_long(parse &parser, text_package &p)
{
    for (auto const &text : p)
        parser(text);
    return true;
}

int main(int argc, char *argv[])
{
    unit_test<parse, string> unit(test_simple, "testing! this is a test");
    unit.get_config().name = "test_simple";
    cout << unit.start() << endl;

    if (argc == 2)
    {
        try {
            auto package = text_package(argv[1]);
            cout << "Reading: " << package.size() << " files" << endl;
            unit_test<parse, text_package> unit2(test_long, package);
            unit2.get_config().iterations = 100;
            unit2.get_config().name = "long parse";
            cout << unit2.start() << endl;
            cout << unit2.get_result().passed << endl;
        }
        catch(const text_package_error &err) {
            cout << err << endl;
        }
    }
    else
        cout << "Unable to perform long test (no directory given)" << endl;
    return 0;
}

