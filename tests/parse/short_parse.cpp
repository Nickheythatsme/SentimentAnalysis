#include <fstream>
#include <iostream>
#include <string>
#include "../testing_classes/case.hpp"
#include "../text_package.h"
#include "parse.h"

using namespace std;

/*
 * Test preconfigured text
 */
bool test_simple()
{
    parse parser;
    parser("testing! this is a test");
    auto len = (parser.size() >= 5) ? 5 : parser.size() - 1;

    cout << "words parsed: " << parser.size() << endl;
    for(const auto &c : parser)
    {
        cout << '"' << c << '"' << endl;
    }
    return parser.size() == 5;
}

int main(int argc, char *argv[])
{
    return !test_simple(); // Return 0 for success.
}

