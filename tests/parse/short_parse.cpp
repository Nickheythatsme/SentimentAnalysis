#include <fstream>
#include <iostream>
#include <string>
#include "../testing_classes/case.hpp"
#include "../text_package.h"
#include "parse.h"

using namespace std;

bool test_simple()
{
    parse parser("testing! this is a test");
    auto len = (parser.size() >= 5) ? 5 : parser.size() - 1;

    cout << "words parsed: " << parser.size() << endl;
    cout << "First " << len << " words: " << endl;
    for(int i=0; i < len; ++i)
    {
        cout << '"' << parser[i] << '"' << endl;
    }
    return parser.size() == 5;
}

int main(int argc, char *argv[])
{
    test_case case1("simple parse test",test_simple);
    case1.start();
    cout << case1.get_result() << endl;

    return !(case1.get_result().passed); // Return '0' for success
}

