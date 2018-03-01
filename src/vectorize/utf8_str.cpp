#include "utf8_str.h"

// CONSTRUCTOR
utf8_str::utf8_str()
{
}

// CONSTRUCTOR with arguments
utf8_str::utf8_str(const char* obj)
{
}

// COPY CONSTRUCTOR
utf8_str::utf8_str(const utf8_str &obj)
{
}

// MOVE CONSTURCTOR
utf8_str::utf8_str(utf8_str&& obj) :
    data {std::move(obj.data)}
{
}

// DESTRUCTOR
utf8_str::~utf8_str()
{
}

// Retrieve one character at index x. If x is negative, the index value
// will be subracted from the end (so -1 is the end).
char utf8_str::operator[](int x) const
{
	return '\0';
}

int char_len(signed char f)
{
	return -1;
}

std::ostream& display_char(std::ostream &out, const char *c)
{
	return out;
}
