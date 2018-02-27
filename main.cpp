#include "parse.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <memory>
#include "utf8_str.h"

#undef DEFAULT_PATH
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define DEFAULT_PATH "C:\\Users\\njgro\\Programming\\SentimentAnalysis\\data\\test\\UTF8\\sample.txt"
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

void test_utf8_class(const char *o);
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

    fin.seekg (0, fin.end);
    len = fin.tellg();
    fin.seekg (0, fin.beg);

    cout << len << endl;
    buff = new char[len + 1];

    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');

    cout << buff << endl;
    test_utf8_class(buff);

    delete [] buff;
    buff = nullptr;

    return 0;
}

void test_utf8_class(const char *o)
{
    utf8_str f("this!");
    cout << f << endl;
}
