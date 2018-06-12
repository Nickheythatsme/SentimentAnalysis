#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include "utf8_manip.h"

#ifndef VECTORIZE_PARSE_
#define VECTORIZE_PARSE_

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

using s_vector=std::vector<std::string>;

class parse : public s_vector
{
public:
	parse();
	explicit parse(const char* delims);
	explicit parse(const char* delims, const std::string &str);
	parse(const parse &obj);
	explicit parse(parse&& rhs);
	~parse();
	parse& operator()(const std::string &str);
	parse& operator=(const parse &obj);
	parse& operator=(parse &&rhs);
protected:
private:
    long _parse(const char *str);

    static char default_delims[];
    char *delims;
    utf8_manip manip;
};

#endif // VECTORIZE_PARSE_
