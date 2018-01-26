//
// Created by nick on 1/24/18.
//

#include <cstring>
#include "parse.h"

/* Default delimeters for parsing words */
char parse::default_delims[] = ".,;?! '\"[](){}";

// DEFAULT CONSTRUCTOR
parse::parse()
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    delims = default_delims;
}

// CONSTRUCTOR
parse::parse(const string &text)
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    // Set the delimeters
    delims   = default_delims;

    // Add the text to the queue
    to_parse.emplace(clean(text));
}

// COPY CONSTRUCTOR
parse::parse(const parse &obj)
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    if( obj.delims != default_delims ) {
        delims = new char[strlen(obj.delims) + 1];
        strcpy(delims, obj.delims);
    }
    else
        delims = default_delims;

    // Copy queue
    to_parse = obj.to_parse;

    // Copy list of parsed words
    word_list = obj.word_list;
}

/* Add the words from obj.word_list and add the queue from obj.queue */
parse& parse::operator=(const parse &src)
{
    // Lock the queue
    std::lock_guard<mutex> g(queue_lock);

    // Copy queue
    to_parse = src.to_parse;

    // Copy list of parsed words
    word_list = src.word_list;

    // Copy the delimeters
    if( src.delims != default_delims )
    {
        delims = new char[strlen(src.delims) + 1];
        strcpy(delims, src.delims);
    }
    else
        delims = default_delims;

    return *this;
}

// TODO finish operator+=
/* Copy the words from obj.word_list and add the queue from obj.queue */
parse& operator+=(parse &dest, parse &src)
{
    // don't actually take the locks yet
    std::unique_lock<std::mutex> lock1(dest.queue_lock,   std::defer_lock);
    std::unique_lock<std::mutex> lock2(src.queue_lock, std::defer_lock);
              
    // lock both unique_locks without deadlock
    // TODO handle exception where lock1 is aquired but lock2 is not
    std::lock(lock1, lock2);

    // Copy the queue. CREATES NEW QUEUE
    // TODO find a solution to copying queues so the we don't COPY, only ADD
    auto temp_q = src.to_parse;
    while(!dest.to_parse.empty())
    {
        temp_q.emplace( dest.to_parse.front() );
        dest.to_parse.pop();
    }
    dest.to_parse = temp_q;

    // Copy the parsed word list
    for(auto const &a : src.word_list)
        dest.word_list.emplace_back(a);
}

// DESTRUCTOR
parse::~parse()
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    if( delims != default_delims )
        delete [] delims;

    word_list.clear();
}

/*
 * Add text that will be parsed. Adds another node onto the queue
 */
void parse::add_text(const string &text)
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    // TESTED this does not make additional copies. Only one from the cleaned function.
    to_parse.emplace( clean(text) );
}

/* 
 * Change the default delimeters for this 
 * instance of the class 
 */
void parse::set_delimeters(const char *new_delims)
{
    delims = new char[strlen(new_delims) + 1];
    strcpy(delims, new_delims);
}

/*
 * Parse text without making a new class instance
 * Returns:
 * list of parsed words.
 */
const std::list<string>& parse::parse_words()
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    while(!to_parse.empty())
    {
        parse_text(to_parse.front());
        to_parse.pop();
    }
    return word_list;
}

/*
 * Parse the text
 * Returns:
 *  SUCCESS: number of words parsed
 *  FAILURE: -1
 */
void parse::parse_text(const string& text)
{
    char buff[1024];
    auto i=0, j=0;

    for(i = 0; i < text.length(); ++i)
    {
        if( test_char(text[i], delims) ){
            buff[j] = '\0';
            word_list.emplace_back(string(buff));
            while(text[i] && test_char(text[i], delims))
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
    while(*delims && c != *delims)
        ++delims;
    return *delims != '\0';
}

/*STATIC
 * Lower all the characters in a string
 */
string& parse::lowerize(string &to_lower)
{
    for(auto &a : to_lower)
        a = tolower(a);
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
