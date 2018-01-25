//
// Created by nick on 1/24/18.
//

#ifndef SENTIMENTANALYSIS_PARSE_H
#define SENTIMENTANALYSIS_PARSE_H

#include <string>
#include <list>

using std::string;
/*
 * Parse words from text. Does not format words into windows,
 * only separates based on spaces/punctuation
 */
class parse {
public:
    parse();
    parse(const string &text);
    parse(const parse &obj);
    virtual ~parse();
    size_t add_text(const string &text);
    void set_delimeters(const char *delims);
    static std::list<string> parse_text(const string& text);
protected:
    string to_parse;
    std::list<string> words;
private:
    static unsigned long parse_text(std::list<string> &words, const string& text, const char *delims);
    static int test_char(char c, const char *delims);
    static char default_delims[]; /* Default delimeters */
    char *delims;
};


#endif //SENTIMENTANALYSIS_PARSE_H
