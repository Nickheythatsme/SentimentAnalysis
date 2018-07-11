#include <iostream>
#include <map>
#include <string>
#include "parse.h"
#include "btree.hpp"
#include "text_package.h"

#ifdef __WIND32 | __WIN64
#define DIR_DELIM '\\'
#else
#define DIR_DELIM '/'
#endif

using namespace std;

bool strgtr(const string &lhs, const string &rhs)
{
	auto min_size = min(lhs.size(), rhs.size());
	auto i = 0;
	for (; i < min_size; ++i)
	{
		if (lhs[i] != rhs[i])
		{
			return lhs[i] > rhs[i];
		}
	}
	return lhs.size() > rhs.size();
}

auto count_words(std::vector<string> &words)
{
	parse parser;
	for (const auto &word : words)
	{
		parser(word);
	}

	map < string, size_t, bool(*)(const string&, const string&)> count(strgtr);
	for (auto &word : parser)
	{
		count[std::move(word)] += 1;
	}
	for (const auto & word_num : count)
	{
		cout << "word: " << word_num.first << "\tcount: " << word_num.second << endl;
	}
}

int main(int argc, char **argv)
{
    // Make the text package
    text_package package;

    if (argc < 2)
    {
        cout << "usage: ./vectorize [text] [directories] [...]" << endl;
        exit(EXIT_FAILURE);
    }

    // Load text files from directories
    for (size_t i=1; i<argc; ++i)
    {
        string dir { argv[i] };

        // Append '*' or '/*' so that glob works
        if (DIR_DELIM != dir.back())
        {
            dir += DIR_DELIM;
        }
        if ('*' != dir.back())
        {
            dir += '*';
        }

        cout << "Reading files from: " << dir << endl;
        package.load_files(dir);
    }

	count_words(package);

    return 0;
}
