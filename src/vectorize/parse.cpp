#include "parse.h"

// CONSTRUCTOR
parse::parse() :
	std::vector<std::string>()
{
}

// CONSTRUCTOR with arguments 
parse::parse(const std::string & _delims) :
	std::vector<std::string>()
{
	delims = std::string(_delims);
}

// COPY CONSTRUCTOR
parse::parse(const parse & obj) :
	std::vector<std::string>(obj)
{
	delims = obj.delims;
}

// Move constructor
parse::parse(parse && rhs) :
	std::vector<std::string>(rhs)
{
	delims = std::move(rhs.delims);
}

parse& parse::operator()(const std::string str)
{
	_parse(str.c_str());
	return *this;
}

parse& parse:: operator=(const parse &obj)
{
	this->std::vector<std::string>::operator=(obj);
	delims = obj.delims;
	return *this;
}

// Parse the UTF8 string and split it based on the delimiters
int parse::_parse(const char *str)
{
	int i=0, char_len;
	char buff[MAX_LEN];

	printf("_parse\n");
	while (*str)
	{
		assert(i < 1024);
		char_len = character_length(*str);

		if (!test_character(str) || i >= MAX_LEN)
		{
			buff[i] = '\0';
			if (i >= MIN_LEN)
				this->emplace_back(std::string(buff));
			i = 0;
			buff[i] = '\0';

			do {
				++str;
				--char_len;
			} while (*str && char_len >= 0);
		}
		else
			for (; *str && char_len >= 0 && i < 1024; ++i, ++str, --char_len)
				buff[i] = *str;
	}
	return this->size();
}

// TODO finish test_character function
int parse::test_character(const char *str)
{
	int len = character_length(*str);
	for (int i = 0; i < len; ++i)
		printf("%c", str[i]);

	if (*str == 'A')
		return 0;
	return 1;
}

/*
STATIC
test the length of a character, returns the length of the UTF character*/
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
