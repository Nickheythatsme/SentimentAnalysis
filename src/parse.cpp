//
// Created by nick on 1/24/18.
//

#include <cstring>
#include "parse.h"

/* Default delimeters for parsing words */
char parse::default_delims[] = ".,;?! '\"[](){}“";

// CONSTRUCTOR
parse::parse() noexcept : std::vector<string>()
{
    delims = new char[strlen(default_delims) + 1];
    strcpy(delims, default_delims);
}

// CONSTRUCTOR with arguments
parse::parse(const string &text) : std::vector<string>()
{
    delims = new char[strlen(default_delims) + 1];
    strcpy(delims, default_delims);
    _parse(text);
}

// CONSTRUCTOR with arguments
parse::parse(const string &text, const char *new_delims) : std::vector<string>()
{
    delims = new char[strlen(new_delims) + 1];
    strcpy(delims, new_delims);
    _parse(text);
}

// CONSTRUCTOR with arguments
parse::parse(const char *new_delims) : std::vector<string>()
{
    delims = new char[strlen(new_delims) + 1];
    strcpy(delims, new_delims);
}

// COPY CONSTRUCTOR
parse::parse(const parse &obj) : std::vector<string>(obj)
{
    delims = new char[strlen(obj.delims) + 1];
    strcpy(delims, obj.delims);
}

// DESTRUCTOR
parse::~parse()
{
    delete [] delims;
}

/*
 * parse the text based on specified delimiters which DEFAULT to default_delims
 * RETURNS vector of parsed words
 */
parse& parse::add_text(const string &text)
{
    _parse(text);
    return *this;
}

/*
 * parse the text based on specified delimiters which DEFAULT to default_delims
 * RETURNS vector of parsed words
 */
parse& parse::add_text(const std::vector<string> &texts)
{
    std::vector<string> words;
    for (auto const &a : texts)
        _parse(a);

    return *this;
}

/* Change the delimiters for parsing */
void parse::set_delimiters(const char* new_delims)
{
    delete [] delims;
    delims = new char[strlen(new_delims) + 1];
    strcpy(delims, new_delims);
}

/*
 * Commence the parsing of a text string, and return a list of parsed words
 */
void parse::_parse(const string &text)
{
    char buff[1024];
    auto i = 0, j = 0;

    for (i = 0; i < text.length(); ++i) {
        if (test_char(text[i], delims)) {
            buff[j] = '\0';
            if( j > 1 )
                this->emplace_back(string(buff));
            while (text[i] && test_char(text[i], delims))
                ++i;
            j = 0;
            buff[j] = '\0';
        }
        buff[j++] = text[i];
    }
}

/*
 * STATIC
 * Test whether a character is a delimiter
 * RETURNS:
 * 0 if it's NOT a delim,
 * not 0 if it is
 */
int parse::test_char(char c, const char *delims)
{
    while (*delims && c != *delims)
        ++delims;
    return *delims != '\0';
}

/*
 * STATIC
 * Lower all the characters in a string
 */
string &parse::lowerize(string &to_lower)
{
    for (auto &a : to_lower)
        a = (char) tolower(a);
    return to_lower;
}

/*
 * STATIC
 * Make a copy and then clean the text.
 * Returns a forward reference to the text
 */
string parse::clean(const string &text)
{
    string cleaned = text;

    // Insert cleaning functions
    return lowerize(cleaned);
}

