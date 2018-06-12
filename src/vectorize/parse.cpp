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

// CONSTRUCTOR with arguments
parse::parse(const char* _delims, const std::string &str) :
	std::vector<std::string>()
{
    delims = new char[strlen(_delims) + 1];
    strcpy(delims, _delims);
    this->operator()(str);
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

// DESTRUCTOR
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
    std::vector<std::string>::operator=(obj);

    delete [] delims;
    delims = new char[strlen(obj.delims) + 1];
    strcpy(delims, obj.delims);

	return *this;
}

/*
 * Assignment move operator
 */
parse& parse::operator=(parse &&rhs)
{
    std::vector<std::string>::operator=(std::move(rhs));
    delims = rhs.delims;
    rhs.delims = nullptr;

    return *this;
}

// Parse the UTF8 string and split it based on the delimiters
long parse::_parse(const char *str)
{
	int buff_index=0, char_len;
	char* buff = new char[MAX_LEN];
    char* buff_head = buff;


	while (*str) {
		char_len = manip.character_length(*str);
        if (!manip.test_character(str, delims, char_len) && char_len < MAX_LEN)
		{
            manip.copy_character(str, buff, MAX_LEN-char_len, char_len);
            auto increment = sizeof(char) * char_len;

            // move to the next char
            str += increment; 
            buff += increment;
            buff_index += 1;
		}
        else
		{
            // Test the length of the word, add it if passed
			if (buff_index > MIN_LEN) {
                *buff = '\0';
				this->emplace_back(std::string(buff_head));
            }
            buff = buff_head;
            buff_index = 0;

            // Skip this character since we know it's bad
            str += sizeof(char) * char_len; // move to the next char

            // Find the new char len
            char_len = manip.character_length(*str);

            // Keep moving until we find a good character
            while(*str && manip.test_character(str, delims, char_len))
            {
                str += sizeof(char) * char_len; // move to the next char

                // Find the new char len
                char_len = manip.character_length(*str);
            }
		}
	}
    if (buff_index > MIN_LEN) {
        this->emplace_back(std::string(buff_head));
    }
    delete [] buff_head;
	return (long) this->size();
}

