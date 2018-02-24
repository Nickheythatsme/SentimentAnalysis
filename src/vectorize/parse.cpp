#include "parse.h"

parse::parse() :
	std::vector<std::string>()
{
}

parse::parse(const std::string & _delims) :
	std::vector<std::string>()
{
	delims = std::string(_delims);
}

parse::parse(const parse & obj) :
	std::vector<std::string>(obj)
{
	delims = obj.delims;
}

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

int parse::_parse(const char *str)
{
	int i = 0, j = 0, char_len = 0;
	char buff[1024];

	while (*str)
	{
		char_len = character_length(*str);
		if (!test_character(str))
		{
			buff[i] = '\0';
			if (i > 2)
				this->emplace_back(std::string(buff));
			i = 0;
			buff[i] = '\0';
		}
		else
			for (j = 0; j < char_len && i < 1024; ++i, ++j, ++str)
				buff[i] = *str;
	}
}

int parse::test_character(const char *str)
{
	return 1;
}

/*
STATIC
test the length of a character, returns the length of the UTF character*/
int parse::character_length(char f)
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
