#include <memory>
#include <cstring>
#include <ostream>

#ifndef _VECTORIZE_UTF8_STR_
#define _VECTORIZE_UTF8_STR_

// Easily make a unique_ptr for a char array
using unique_ptr_char = std::unique_ptr<char[]>;

class utf8_str
{
public:
	utf8_str();
    utf8_str(const char* obj);
	utf8_str(const utf8_str &obj);
	utf8_str(utf8_str&& obj);
	~utf8_str();

	// Retrieve one character at index x. If x is negative, the index value
	// will be subracted from the end (so -1 is the end).
	char operator[](int x) const;

	// Returns true if there is the char ptr is NULL
	bool operator!() const;

	// Display the string on the ostream out object
	friend std::ostream& operator<<(std::ostream& out, const utf8_str &obj);

	// Add two utf8_str objects together and return a new object
	friend utf8_str operator+(const utf8_str &obj1, const utf8_str &obj2);

	// Add one utf8_str to this utf8_str and return the original 
	utf8_str& operator+=(const utf8_str &obj);

	// Assignment operator
	utf8_str& operator=(const utf8_str &obj);

    // Increment operator - used to move to the next character (may be multiple bytes)
    // prefix
    utf8_str& operator++();
    // postfix
    utf8_str operator++(int);
protected:

	// Display to ostream out object
	std::ostream& display(std::ostream& out) const;

	// Set the data in this object to match rhs
	void set(const utf8_str &rhs);

	// Clear the character ptf
	void clear();
private:
	static int char_len(unsigned char f);
	static std::ostream& display_char(std::ostream &out, const char *c);
	static bool next_char(char *& f);

	unique_ptr_char data;
};

#endif //_VECTORIZE_UTF8_STR_
