#include "parse.h"

// Assign the default delimiters
char parse::default_delims[] = "@ .?!\t\n";

// CONSTRUCTOR
parse::parse() :
	std::vector<std::string>()
{
    delims = new char[strlen(parse::default_delims) + 1];
    strcpy(delims, parse::default_delims);
}

// CONSTRUCTOR with arguments 
parse::parse(const char* _delims) :
	std::vector<std::string>()
{
    delims = new char[strlen(_delims) + 1];
    strcpy(delims, _delims);
}

// COPY CONSTRUCTOR
parse::parse(const parse &obj) :
	std::vector<std::string>(obj)
{
    delims = new char[strlen(obj.delims) + 1];
    strcpy(delims, obj.delims);
}

// Move constructor
parse::parse(parse && rhs) :
	std::vector<std::string>(std::move(rhs))
{
    delims = rhs.delims;
    rhs.delims = nullptr;
}

parse::~parse()
{
    if (delims) {
        delete[] delims;
        delims = nullptr;
    }
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
    //TODO infinite recursion here? This should not call parse's assignment operator, rather the parent of parse, vector
    std::vector<std::string>::operator=(obj);

    delete [] delims;
    delims = new char[strlen(obj.delims) + 1];
    strcpy(delims, obj.delims);

	return *this;
}

// Parse the UTF8 string and split it based on the delimiters
long parse::_parse(const char *str)
{
	int buff_index=0, char_len;
	char buff[MAX_LEN];

	while (*str) {
		char_len = manip.character_length(*str);
        if (!manip.test_character(str, delims, char_len))
		{
            manip.copy_character(str, buff, MAX_LEN-char_len, char_len);

            /*

            if (1 == char_len){
                buff[buff_index] = *str;
                ++str;
                ++buff_index;
            }
            else
                for (int i=0; i < char_len; ++i)
                {
                    buff[buff_index] = *str;
                    ++str;
                    ++buff_index;
                }
            */
		}
        else
		{
			if (buff_index > MIN_LEN)
				this->emplace_back(std::string(buff));
            buff_index = 0;

            // Skip this character since we know it's bad
            for (int i=0; i < char_len; ++i)
                ++str;

            // Keep moving until we find a good character
            while(*str && manip.test_character(str, delims, char_len))
            {
                char_len = manip.character_length(*str); //don't call this more than we need
                for (int i=0; i < char_len; ++i)
                    ++str;
            }
		}

	}
	return (long) this->size();
}

