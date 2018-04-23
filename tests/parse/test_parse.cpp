#include "test_parse.h"

bool test_parse(const char *text)
{
    parse parser;

    try{
        parser(text);
        cout << "words: " << endl;
        for (auto const &w : parser)
            cout << w << endl;
    }
    catch(...)
    {
        cerr << "Error parsing text" << endl;
        return false;
    }

    return test_object<parse>(parser);
}
