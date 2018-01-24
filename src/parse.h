//
// Created by nick on 1/24/18.
//

#ifndef SENTIMENTANALYSIS_PARSE_H
#define SENTIMENTANALYSIS_PARSE_H

#include <string>
#include <vector>

using std::string;
using std::vector;
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
    static vector<string> parse_text(const string& text);
protected:
    string to_parse;
    vector<string> words;
private:
    static unsigned long parse_text(vector<string> &words, const string& text, const char *delims);
    static int test_char(char c, const char *delims);
    static char default_delims[]; /* Default delimeters */
    char *delims;
};


#endif //SENTIMENTANALYSIS_PARSE_H
