#include "test_parse.h"

bool test_parse(const char *text)
{
    if (!test_copy(text)){
        cerr << "Error parsing text" << endl;
        return false;
    }

    if (!test_copy(text)){
        cerr << "Error copying parse object" << endl;
        return false;
    }

    if (!test_move(text)){
        cerr << "Error moving parse object" << endl;
        return false;
    }

    /*
     * TODO implement assignment operator
    if (!test_assignment(text)){
        cerr << "Error assigning parse object" << endl;
        return false;
    }
    */

    return true;
}

/*
 * Test to see if the parser can parse
 */
bool test_parse_functionality(const char *text)
{
    try{
        parse parser;
        parser(text);
        if (parser.empty())
            return false;
    }
    catch(std::bad_alloc &alloc){
        cerr << "Allocation error while parsing: " << alloc.what() << endl;
        return false;
    }


    return true;
}

bool test_copy(const char *text)
{
    parse parse1;
    parse1(text);
    try{
        auto parse2 = parse1;
        if (parse2.empty())
            return false;
    }
    catch(std::bad_alloc &alloc){
        cerr << "Allocation error while copying: " << alloc.what() << endl;
        return false;
    }
    return true;
}

bool test_move(const char *text)
{
    parse parse1;
    parse1(text);

    try{
        parse parse2(std::move(parse1));
        if (parse2.empty() || !parse1.empty())
            return false;
    }
    catch(std::bad_alloc &alloc){
        cerr << "Allocation error while moving parser: " << alloc.what() << endl;
        return false;
    }

    return true;
}

bool test_assignment(const char *text)
{
    int len = strlen(text);
    parse parse1;
    parse parse2;

    parse1(text);

    const char *text2 = text;
    for (int i=0; i < len; ++i)
        ++text2;
    parse2(text2);

    try{
        parse1 = parse2;
    }
    catch(std::bad_alloc &alloc)
    {
        cerr << "Error assigning parse objects" << endl;
        return false;
    }

    if (parse1[0] != parse2[0])
        return false;

    return true;
}
