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
    cout << unit.start() << endl;

    if (argc == 2)
        auto package = text_package(argv[1]);
    else
        cout << "Unable to perform long test (no directory given)" << endl;
    // unit_test<parse, vector<string>> unit2(test_long, argv[1]);
}
