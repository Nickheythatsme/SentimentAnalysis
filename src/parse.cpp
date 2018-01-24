//
// Created by nick on 1/24/18.
//

#include <cstring>
#include <iostream>
#include "parse.h"

/* Default delimeters for parsing words */
char parse::default_delims[] = ".,;?! '\"[](){}";

// DEFAULT CONSTRUCTOR
parse::parse()
{
    delims = default_delims;
}

// CONSTRUCTOR
parse::parse(const string &text)
{
    delims = default_delims;
}

// COPY CONSTRUCTOR
parse::parse(const parse &obj)
{
    if( obj.delims != default_delims ) {
        delims = new char[strlen(obj.delims) + 1];
        strcpy(delims, obj.delims);
    }
    else
        delims = default_delims;

    to_parse = obj.to_parse;
    words    = obj.words;
}

// DESTRUCTOR
parse::~parse()
{
    if( delims != default_delims )
        delete [] delims;
}

/* Add text that will be parsed. */
size_t parse::add_text(const string &text)
{
    to_parse += text;
    return to_parse.length();
}

/* Change the default delimeters for this instance of the class */
void parse::set_delimeters(const char *new_delims)
{
    delims = new char[strlen(new_delims) + 1];
    strcpy(delims, new_delims);
}

/*
 * STATIC
 * Parse text without making a new class instance
 * Returns:
 * vector of parsed words.
 */
vector<string> parse::parse_text(const string &text)
{
    vector<string> words;
    parse_text(words, text, parse::default_delims);
    return words;
}

/*
 * Parse the text
 * Returns:
 *  SUCCESS: number of words parsed
 *  FAILURE: -1
 */
unsigned long parse::parse_text(vector<string> &words, const string &text, const char *delims)
{
    char buff[1024];
    int i = 0;

    for(auto c : text)
    {
        if( test_char(c,delims) )
        {
            if(i > 2) {
                buff[i] = '\0';
                std::cout << buff << std::endl;
                words.emplace_back(string(buff));
            }
            while(c && test_char(++c,delims))
                ++c;
            i = 0;
            buff[i] = '\0';
        }
        buff[i++] = c;
    }
    return words.size();
}

/*
 * Test whether a character is a delimiter
 * RETURNS:
 * 0 if it's NOT a delim,
 * not 0 if it is
 */
int parse::test_char(char c, const char *delims)
{
    while(*delims && c != *delims)
        ++delims;
    return *delims != '\0';
}
