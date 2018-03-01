#include <vector>
#include <string>
#include <cassert>

#ifndef VECTORIZE_PARSE_
#define VECTORIZE_PARSE_

#ifdef _DEBUG
	#define DEBUG_MESSAGE(x) printf("%s\n",x)
#endif
#define default_delims ".?!���";
#define MAX_LEN 1024
#define MIN_LEN 2

class parse : public std::vector<std::string>
{
public:
	parse();
	parse(const std::string &delims);
	parse(const parse &obj);
	parse(parse&& rhs);
	~parse() = default;
	parse& operator()(const std::string str);
	parse& operator=(const parse &obj);
protected:
private:
	int _parse(const char *str);
	int test_character(const char *str);
	static int character_length(signed char f);
	std::string delims;
};

#endif // VECTORIZE_PARSE_