//
// Created by nick on 1/24/18.
//

#ifndef SENTIMENTANALYSIS_PARSE_H
#define SENTIMENTANALYSIS_PARSE_H


#include <iostream>
#include <string>
#include <vector>
#include <queue>

#define MIN_CHAR 2 // Minimum number of characters before a word is added to the parsed list

using std::string;
/*
 * Parse words from text. Does not format words into windows,
 * seperates based on default_delims or specified delimiters
 */
class parse : public std::vector<string>
{
public:
    /* Constructors/Destructors */
    parse() noexcept;
    explicit parse(const string &text);
    explicit parse(const string &text, const char *new_delims);
    explicit parse(const char *new_delims);
    parse(const parse &obj);
    virtual ~parse();

    /* Parse the text based on specific delimiters and return the words as a vector */
    parse& add_text(const string &text);

    /* Parse all the text in a vector and return those words in one vector */
    parse& add_text(const std::vector<string> &texts);

    /* Change the delimiters for parsing */
    void set_delimiters(const char* delims);
protected:
private:
    /* Commence the parsing of a text string, and return a list of parsed words */
    void _parse(const string &text);

    /* Test if a character is a delimiter */
    static int test_char(char c, const char *delims);

    /* Lower all the characters in a string */
    static string &lowerize(string &to_lower);

    /* Make a copy and clean the text */
    static string clean(const string &to_clean);

    static char default_delims[]; /* Default delimiters */
    char *delims;
};


#endif //SENTIMENTANALYSIS_PARSE_H
