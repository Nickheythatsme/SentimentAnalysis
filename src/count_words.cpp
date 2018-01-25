//
// Created by Nick Grout on 1/24/18.
//

#include "count_words.h"

// DEFAULT CONSTRUCTOR
count_words::count_words() :
    parse()
{

}

// CONSTRUCTOR
count_words::count_words(const string &text) :
    parse(text)
{

}

// COPY CONSTRUCTOR
count_words::count_words(const count_words &obj) :
    parse(obj)
{

}

// TODO during implementation of word counting, use this code as reference:
/*
    std::map<string,int> m;
    m["one"] = 1;
    m["two"] = 2;
    cout << m.count("three") << endl; // 0
    cout << m.count("two") << endl;   // 1
    m["two"] += 1;
*/
