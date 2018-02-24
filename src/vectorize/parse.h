#include <vector>
#include <string>

#ifndef VECTORIZE_PARSE_
#define VECTORIZE_PARSE_

#define default_delims ".?!†•€";

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
	static int character_length(char f);
	std::string delims;
};

#endif // VECTORIZE_PARSE_