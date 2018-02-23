#include "parse.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

using std::cout;
using std::endl;

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

int parse_utf8(char *str, int len)
{
    int num_chars = 0;
    uint8_t byte;

    for (int i = 0; i < len && *str; ++i)
    {
        // Parse individual characters
        byte = (uint8_t) *str;

        // One byte character
        if (byte <= 0x7f)
        {
            printf("%c",*str);
            ++str;
        }

        // Two byte character
        else if (byte >= 0xc2 && byte <= 0xdf)
        {
            for(int i = 0; i < 2; ++i)
            {
                printf("%c",*str);
                ++str;
            }
        }

        // Three byte character
        else if (byte >= 0xe0 && byte <= 0xef)
        {
            for(int i = 0; i < 3; ++i)
            {
                printf("%c",*str);
                ++str;
            }
        }

        // Four byte character
        else if (byte >= 0xf0)
        {
            for(int i = 0; i < 4; ++i)
            {
                printf("%c",*str);
                ++str;
            }
        }

        num_chars += 1;

    }
    printf("\n");

    return num_chars;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Usage ./SentimentAnalysis [files]" << endl;
		exit(EXIT_FAILURE);
	}
    std::ifstream fin(argv[1]);
    int len;
    char *buff;

    fin.seekg (0, fin.end);
    len = fin.tellg();
    fin.seekg (0, fin.beg);

    cout << len << endl;
    buff = new char[len + 1];

    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');

    cout << "Number of chars: " << parse_utf8(buff, strlen(buff) ) << endl;

    return 0;
}

