#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

#ifndef VECTORIZE_PARSE_
#define VECTORIZE_PARSE_

#ifdef _DEBUG
	#define DEBUG_MESSAGE(x) printf("%s\n",x)
#endif

#define MAX_LEN 1024
#define MIN_LEN 1

/*
 * So for UTF-8 encoding:
 *  0x00 - 0x7f is regular 1 byte ASCII character
 *  0x80 - 0xBF means this is a continuing byte for a multi-byte character
 *  0xC2 - 0xDF is the beginning byte of a two byte character
 *  0xE0 - 0xEF is the beginning byte of a three byte character
 *  0xF0 - 0xFF is the beginning byte of a four byte sequence
 *
 *  len      1st byte
 *  1 bytes  0xxxxxxx
 *  2 bytes  110xxxxx
 *  3 bytes  1110xxxx
 *  4 bytes  11110xxx
 */

typedef unsigned char uchar_t;

class parse : public std::vector<std::string>
{
public:
	parse();
	parse(const char* delims);
	parse(const parse &obj);
	parse(parse&& rhs);
	~parse() = default;
	parse& operator()(const std::string &str);
	parse& operator=(const parse &obj);
protected:
private:
	int _parse(const char *str);
    static char default_delims[];
	int test_character(const char *str, int len) const;
	static int character_length(signed char f);
    static int next_character(char *&str);
    static int next_character(char *&str, int len);
	static void copy_character(const char *str, char *buff, int char_len, int &buff_index);
	char *delims;
};

#endif // VECTORIZE_PARSE_
