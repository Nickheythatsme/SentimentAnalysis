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
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    delims = default_delims;
    head = tail = NULL;
}

// CONSTRUCTOR
parse::parse(const string &text)
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    delims   = default_delims;
    head = new to_parse(text);
    tail = head;
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

    word_list = obj.word_list;
    copy_LLL(obj.head, this -> head);
}

// TODO finish operator=
/* Add the words from obj.word_list and add the queue from obj.queue */
parse& parse::operator=(parse &src)
{
    // don't actually take the locks yet
    std::unique_lock<std::mutex> lock1(src.queue_lock,   std::defer_lock);
    std::unique_lock<std::mutex> lock2(this->queue_lock, std::defer_lock);
              
    // lock both unique_locks without deadlock
    // TODO handle exception where lock1 is aquired but lock2 is not
    std::lock(lock1, lock2);
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
}

/*
 * Copy the LLL queue of another parse object. The object's head ptr is
 * recursivelly copied to this head ptr.
 */
void parse::copy_LLL(const struct to_parse *obj_head, struct to_parse *&head)
{
    if(!obj_head) 
    {
        head = NULL;
        return;
    }
    head = new to_parse(obj_head -> text);
    this -> tail = head; // Move the tail with the queue
    return copy_LLL(obj_head -> next, head -> next);
}

// DESTRUCTOR
parse::~parse()
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    if( delims != default_delims )
        delete [] delims;
    head = tail = NULL;

    // Clear the queue
    remove_LLL(head);
}

/*
 * Remove the LLL of text to be parsed
 */
void parse::remove_LLL(struct to_parse *&head)
{
    if(!head) return;
    remove_LLL(head -> next);
    delete head -> next;
    return;
}

/* 
 * Add text that will be parsed. Adds another node onto the queue
 */
void parse::add_text(const string &text)
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    // CASE: queue is empty
    if(!head)
    {
        head = new to_parse(text);
        tail = head;
    }

    // CASE: queue is NOT empty
    else
    {
        tail -> next = new to_parse(text);
        tail = tail -> next;
    }
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
 * STATIC
 * Parse text without making a new class instance
 * Returns:
 * list of parsed words.
 */
const std::list<string>& parse::parsed_words()
{
    // Lock the queue 
    std::lock_guard<mutex> g(queue_lock);

    // Only parse if we need to!
    to_parse *temp = head;
    while(head)
    {
        parse_text(head -> text);
        temp = head;
        head = head -> next;
        delete temp;
    }
    tail = NULL;
    return word_list;
}

/*
 * Parse the text
 * Returns:
 *  SUCCESS: number of words parsed
 *  FAILURE: -1
 */
unsigned int parse::parse_text(const string& text)
{
    char buff[1024];
    int i=0, j=0;

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
    return word_list.size();
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
