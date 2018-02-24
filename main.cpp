#include "parse.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <cstring>

#undef DEFAULT_PATH
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define DEFAULT_PATH "C:\\Users\\njgro\\Programming\\SentimentAnalysis\\data\\test\\UTF8\\small.txt"
#else
#define DEFAULT_PATH "../data/test/UTF8/sample.txt"
#endif

using std::cout;
using std::endl;
using std::cin;

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

int parse_utf8(char *str, int len)
{
    int num_chars = 0;
	int num_special_chars = 0;
    uchar_t byte;

    for (int i = 0; i < len && *str; ++i)
    {
        // Parse individual characters
        byte = (uchar_t) *str;

        // One byte character
        if (byte <= 0x7f)
        {
            printf("%c",*str);
            ++str;
        }

        // Two byte character
        else if (byte >= 0xc2 && byte <= 0xdf)
        {
			++num_special_chars;
            for(int i = 0; i < 2; ++i)
            {
                printf("%c",*str);
                ++str;
            }
        }

        // Three byte character
        else if (byte >= 0xe0 && byte <= 0xef)
        {
			++num_special_chars;
            for(int i = 0; i < 3; ++i)
            {
                printf("%c",*str);
                ++str;
            }
        }

        // Four byte character
        else if (byte >= 0xf0)
        {
			++num_special_chars;
            for(int i = 0; i < 4; ++i)
            {
                printf("%c",*str);
                ++str;
            }
        }

        num_chars += 1;

    }
    printf("\n");
	printf("Special characters: %d\n", num_special_chars);

    return num_chars;
}

int main(int argc, char *argv[])
{
	std::string path;
	if (argc < 2)
		path = DEFAULT_PATH;
	else
		path = argv[1];
	cout << "Loading: " << path << endl;
    std::ifstream fin(path);
	if (!fin)
		exit(EXIT_FAILURE);
    int len;
    char *buff;
	parse parser;

    fin.seekg (0, fin.end);
    len = fin.tellg();
    fin.seekg (0, fin.beg);

    cout << len << endl;
    buff = new char[len + 1];

    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');

    //cout << "Number of chars: " << parse_utf8(buff, strlen(buff) ) << endl;
	parser(std::string(buff));
	cout << "Size: " << parser.size() << endl;
	for (auto const &a : parser)
		cout << a << endl;

    delete [] buff;
    buff = nullptr;
	getchar();

    return 0;
}

