#include <vector>
#include <string>
#include <cstring>
#include <mutex>
#include <thread>

#ifndef VECTORIZE_PARSE_
#define VECTORIZE_PARSE_

#define STRING_MAX 800000
#define STRING_MIN 3

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

// used to identify locations of delimiters which will later be removed/ignored
struct delim_location
{
	size_t start; // starting position of the section to trim
	size_t end; // one past the ending location. 
};

class parse : public s_vector
{
public:
	parse();
	explicit parse(s_vector _delims);
	parse(parse&& rhs);
	parse(const parse &obj);
    std::string operator()(const std::string &str);
	parse& operator=(const parse &obj);
	parse& operator=(parse&& rhs);
protected:
private:
    std::string _parse(const char *str);
	size_t identify(const char *str, const char *delim, size_t delim_len, size_t index);
	void insert_sorted(delim_location &&to_insert);
    std::string make_string(const char* str);

	std::vector<delim_location> to_trim;
	std::mutex to_trim_mut;
    s_vector delims;
    static s_vector default_delims;
};

#endif // VECTORIZE_PARSE_
