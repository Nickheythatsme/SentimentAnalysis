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
	std::vector<std::string>(rhs)
{
    delims = rhs.delims;
    rhs.delims = nullptr;
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
 * Assignment opertator
 */
parse& parse:: operator=(const parse &obj)
{
	this->std::vector<std::string>::operator=(obj);

    delete [] delims;
    delims = new char[strlen(obj.delims) + 1];
    strcpy(delims, obj.delims);

	return *this;
}

// Parse the UTF8 string and split it based on the delimiters
int parse::_parse(const char *str)
{
	int buff_index=0, char_len;
	char buff[MAX_LEN];

	while (*str) {
		char_len = character_length(*str);
		if (!test_character(str, char_len))
		{
            for (int i=0; i < char_len; ++i)
            {
                buff[buff_index] = *str;
                ++str;
                ++buff_index;
            }
		}
		else
		{
			if (buff_index > MIN_LEN)
			{
                buff[buff_index] = '\0';
				this->emplace_back(std::string(buff));
			}
            buff_index = 0;
            buff[buff_index] = '\0';

            // Skip this character since we know it's bad
            for (int i=0; i < char_len; ++i)
                ++str;
            // Keep moving until we find a good character
            while(*str && test_character(str, char_len))
            {
                char_len = character_length(*str); //don't call this more than we need
                for (int i=0; i < char_len; ++i)
                    ++str;
            }
		}

	}
	return this->size();
}

/*
 * Test each character in the delimiter string against the current character
 * of str
 */
int parse::test_character(const char *str, int len) const
{
    char *d_str = delims; // delimiter string
    const char *str_head = str; // save the right character of str

    // Find the length of the character to test
    int s_len = character_length(*str);

    while (*d_str)
    {
        // Find the length of the current delimiter character
        int d_len = character_length(*d_str);

        // Skip comparison if they're of differet lengths
        if (d_len == s_len)
        {

            // accumulate the differences
            int diff = 0;
            for (int i=0; i<d_len && 0 == diff; ++i, ++d_str, ++str)
                diff += *d_str - *str;

            // Return 1 if we have a match
            if (diff == 0)
                return 1;

            // reset str to the character we were testing
            str = str_head;
        }
        else
        {
            // Move along the delimiters if we're not comparing this character
            for(int i=0; i < d_len; ++i)
                ++d_str;
        }
    }
    // Return false if we found no matches
    return 0;
}

/*
STATIC
copies one UTF8 character into the buff
checks the boundaries to make sure we don't go past buffer
*/
void parse::copy_character(const char *str, char *buff, int char_len, int &buff_index)
{
	for (;char_len >=0 && buff_index < MAX_LEN && *str; --char_len)
	{
        buff[buff_index] = *str;
		++str;
        ++buff_index;
	}
	buff[buff_index] = '\0';
}

/*
 * STATIC
 * test the length of a character, returns the length of the UTF character
 */
int parse::character_length(signed char f)
{
	int i = 0;
	if (f >= 0)
		return 1;

	while (f < 0)
	{
		f <<= 1;
		++i;
	}
	return i;
}
