#include <fstream>
#include <iostream>
#include <string>
#include "../test_case.h"
#include "parse.h"

using namespace std;

bool test_function(parse &parser, string &text)
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

int main(int argc, char *argv[])
{
    unit_test<parse, string> unit(test_function, "testing! this is a test");
    cout << unit.start() << endl;
}
