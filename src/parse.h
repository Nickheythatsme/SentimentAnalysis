//
// Created by nick on 1/24/18.
//

#ifndef SENTIMENTANALYSIS_PARSE_H
#define SENTIMENTANALYSIS_PARSE_H

#include <string>
#include <list>
#include <mutex>
using std::string;
using std::mutex;

struct to_parse
{
    to_parse(const string &new_text) { text = new_text; next = NULL; }
    ~to_parse() { }
    string text;
    to_parse *next;
};

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
    /* Add text to the to_parse string */
    void add_text(const string &text);
    /* Set the delimeters to another set.
     * Possibly parsing based on periods or commas instead of any punctuation.*/
    void set_delimeters(const char *delims);
    /* Returns a constant ref to the list of parsed words */
    const std::list<string>& parsed_words();
    /* Returns TRUE if there is nothing left to parse.
     * FALSE if otherwise */
    bool finished_parsing() { return !head; }
    /* Add the words from obj.word_list and add the queue from obj.queue */
    parse& operator=(parse &src);
    /* Copy the words from obj.word_list and add the queue from obj.queue */
    friend parse& operator+=(parse &dest, parse &src);
protected:
    std::list<string> word_list;
private:
    /* copy all the nodes from another parse object */
    void copy_LLL(const struct to_parse *obj_head, struct to_parse *&head);
    /* Remove all the nodes in the queue */
    void remove_LLL(struct to_parse *&head);
    /* Commence the parsing of a text string, and add it to the word_list */
    unsigned int parse_text(const string& text);
    static int test_char(char c, const char *delims);

    static char default_delims[]; /* Default delimeters */
    char *delims;
    struct to_parse *head;
    struct to_parse *tail;
    // Lock the queue of text to parse
    mutex queue_lock;
};


#endif //SENTIMENTANALYSIS_PARSE_H
