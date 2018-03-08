#include "test_parse.h"

bool test_parse(const char *text)
{
    parse parser;

    try{
        parser(text);
    }
    catch(...)
    {
        cerr << "Error parsing text" << endl;
        return false;
    }

    return test_object<parse>(parser);
}
