#include "test_parse.h"

bool test_parse(const char *text)
{
    parse parser;

    try{
        parser(text);
        cout << "words parsed: " << parser.size() << endl;
        cout << "First 5 words: " << endl;
        auto len = (parser.size() >= 5) ? 5 : parser.size() - 1;
        for(int i=0; i < len; ++i)
        {
            cout << '"' << parser[i] << '"' << endl;
        }
    }
    catch(...)
    {
        cerr << "Error parsing text" << endl;
        return false;
    }

    return test_object<parse>(parser);
}
