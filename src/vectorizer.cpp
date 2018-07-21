/*
 * Nicholas Grout
 *
 * This is the culmination of the vectorizer.
 * Give this program a pattern to match (wildcard, etc) and it will
 * read all files matching that pattern, or give it a single file.
 *
 * It will currently just parse text
 */
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "parse.h"
#include "btree.hpp"
#include "text_package.h"

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

void lowercase(std::string &str)
{
    for (auto &c : str)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c += 32;
        }
    }
}

bool cmp_pair(const std::pair<std::string,size_t> &lhs, const std::pair<std::string,size_t> &rhs)
{
    return lhs.second > rhs.second;
}

auto count_words(std::vector<string> &words)
{
	parse parser {std::vector<string>{" ", "/>",">","<","(",")",".",",",";","\"","Â","\t","a"}};
	map <string, size_t, bool(*)(const string&, const string&)> count(strgtr);

	for (auto &word : words)
	{
        lowercase(word);
		parser(word);
	}

    for (auto &word : parser)
    {
        count[std::move(word)] += 1;
    }

    // std::sort(count.begin(), count.end(), cmp_pair);
    std::vector<std::pair<string, size_t>> vec;
    for (auto &p : count)
    {
        vec.emplace_back(std::move(p));
    }
    std::sort(vec.begin(), vec.end(), cmp_pair);

	for (const auto & word_num : vec)
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
        cout << "usage: ./vectorize [text directories] [...]" << endl;
        exit(EXIT_FAILURE);
    }

    // Load text files from directories
    for (size_t i=1; i<argc; ++i)
    {
        cout << "Reading files from: " << argv[i] << endl;
        package.load_files(argv[i]);
    }
	count_words(package);
    return 0;
}
