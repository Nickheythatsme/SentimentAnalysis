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
    auto result = unit.start();
    cout << unit.get_result() << endl;

    return 0;
}

