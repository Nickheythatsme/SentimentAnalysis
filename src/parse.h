//
// Created by nick on 1/24/18.
//

#ifndef SENTIMENTANALYSIS_PARSE_H
#define SENTIMENTANALYSIS_PARSE_H


#include <iostream>
#include <string>
#include <list>
#include <mutex>
#include <queue>
using std::string;
using std::mutex;

/*
 * Parse words from text. Does not format words into windows,
 * only separates based on spaces/punctuation
 */
class parse {
public:
    parse();
    explicit parse(const string &text);
    parse(const parse &obj);
    virtual ~parse();
    /* Add text to the to_parse string */
    void add_text(const string &text);

    /* Set the delimeters to another set.
     * Possibly parsing based on periods or commas instead of any punctuation.*/
    void set_delimeters(const char *delims);

    /* Returns a constant ref to the list of parsed words */
    const std::list<string>& parse_words();

    /* Returns TRUE if there is nothing left to parse.
     * FALSE if otherwise */
    bool finished_parsing() { return to_parse.empty(); }

    /* Add the words from obj.word_list and add the queue from obj.queue */
    parse& operator=(const parse &src);

    /* Copy the words from obj.word_list and add the queue from obj.queue */
    friend parse& operator+=(parse &dest, parse &src);
protected:
private:
    /* Commence the parsing of a text string, and add it to the word_list */
    void parse_text(const string& text);

    /* Test if a character is a delimiter */
    static int  test_char(char c, const char *delims);

    /* Lower all the characters in a string */
    static string& lowerize(string &to_lower);

    /* Make a copy and clean the text */
    static string clean(const string &to_clean);

    static char default_delims[]; /* Default delimeters */
    char *delims;

    // Lock the queue of text to parse
    mutex queue_lock;

    /* List of words that have been parsed */
    std::list<string>  word_list;
    std::queue<string> to_parse;
};


#endif //SENTIMENTANALYSIS_PARSE_H
