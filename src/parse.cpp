#include "parse.h"

// Assign the default delimiters
s_vector parse::default_delims = {"?"," ",".",",","\"","'","<br>","</br>","< /br>","< br>"};

// CONSTRUCTOR
parse::parse() :
	s_vector(),
    delims(parse::default_delims)
{
}

// CONSTRUCTOR with arguments 
parse::parse(s_vector _delims) :
	s_vector(),
    delims(std::move(_delims))
{
}

// CONSTRUCTOR with arguments
parse::parse(s_vector _delims, std::string str) :
	s_vector(),
    delims(std::move(_delims))
{
    this->operator()(std::move(str));
}

// COPY CONSTRUCTOR
parse::parse(const parse &obj) :
    s_vector(obj),
    delims(obj.delims)
{
}

// Move constructor
parse::parse(parse && rhs) :
    s_vector(std::move(rhs)),
    delims(std::move(rhs.delims))
{
}


/*
 * Parenthesis operator.
 * Parses the string inside the parenthesis and adds the parsed words to this
 * object (in it's vector)
 */
parse& parse::operator()(const std::string &str)
{
	_parse(str.c_str());
	return *this;
}

/*
 * Assignment operator
 */
parse& parse::operator=(const parse &obj)
{
    s_vector::operator=(obj);
    delims = obj.delims;
	return *this;
}

/*
 * Assignment move operator
 */
parse& parse::operator=(parse &&rhs)
{
    s_vector::operator=(std::move(rhs));
    delims = std::move(rhs.delims);
    return *this;
}

// Parse the UTF8 string and split it based on the delimiters
long parse::_parse(const char *str)
{
    return -1;
}
