#include <string>
#include <ostream>

#ifndef WINDOW_
#define WINDOW_

using std::string;

/* 
 * This is the window class. It stores a window for a bit of text, like a 
 * sentence or fragment of a sentence. It is meant to maintain one instance of
 * surrounding words to represent a bit of their relationship.
 *
 * It is implemented with a DLL, where each node is just a string with a next
 * and prev ptr.
 */

struct word: public string
{
    word()
        : string()
    { next = prev = nullptr; }
    explicit word(const string &obj)
        : string(obj)
    { next = prev = nullptr; }
    word(const word &obj)
        : string(obj)
    { next = prev = nullptr; }

    word *next;
    word *prev;
};

class window
{
public:
    window();
    window(const string *words, size_t len);
    window(const window &obj);
    ~window();

    // Assignment operator
    window &operator=(const window &src);

    // Add words from another window to this window
    window &operator+=(const window &to_add);

    // Add a word to this window (at the end)
    window &operator+=(const string &to_add);

    // Add two windows together to make a new window
    friend window operator+(const window &obj1, const window &ob2);

    // Add a window and a word together to make a new window
    friend window operator+(const window &obj1, const string &ob2);

    // Output all words to the ostream through the extraction operator
    friend std::ostream &operator<<(std::ostream &out, const window &obj);

    // Returns the number of words in the window
    size_t size() const;

    /* Clear all the words in the DLL if they exist */
    void clear();
protected:
    // Out put all words to the ostream, in order
    std::ostream &display(std::ostream &out, const word *head) const;
private:
    // Add a single string word to this window
    void add_word(const string &to_add);

    // Remove all words in this window
    void remove_all(word *head);

    // Copy all of the words in the DLL, recursively
    size_t copy_DLL(const word *obj_head, word *&self_head, word *&self_tail);

    // Recursively add words in a DLL to this window
    void insert_DLL(const word *head);

    // Tail and head pointers for the words in the window
    word *head;
    word *tail;

    // The number of words in the window
    size_t _size;
};

#endif
