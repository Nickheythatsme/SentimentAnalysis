#include "parse.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#undef DEFAULT_PATH
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#define WINPAUSE system("pause");
#else
    #define WINPAUSE
#endif

using std::cout;
using std::endl;
using std::cin;

/* 
 * Get the path from the user, returns false if there was more path than there
 * was buffer
 */
bool get_path(char *&path, const char *message)
{
    char buff[1024];
    bool is_end = true;

    cout << message;

    cin.get(buff, 1024, '\n');
    if (cin.peek() != '\n') is_end=false;
    cin.ignore(1024,'\n');

    path = new char[strlen(buff) + 1];
    strcpy(path,buff);
    return is_end;
}

/*
 * Read the whole contents of a file to the char*
 * Returns
 * 0 or less than 0 if error
 * greater than 0 if success
 */
int read_file(const char *filename, char *&buff)
{
    int len;
    std::ifstream fin(filename);
	if (!fin)
        return -1;

	// Determine file size
    fin.seekg (0, fin.end);
    len = fin.tellg();
    fin.seekg (0, fin.beg);

	// Allocate buff and read in file
    buff = new char[len + 1];
	if (!buff)
        return -1;
    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');
    return len;
}

bool test_parse(const char* buff)
{
    parse parser;
    parser(buff);

    cout << "Parsed: " << parser.size() << " words" << endl;
    cout << "Words: " << endl;
    for (auto &a : parser)
        cout << '\t' << a << endl;
    return true;
}

int main(int argc, char *argv[])
{
	char *path;
    char *buff;
    int len;

    // Assign the path
	if (argc < 2)
        get_path(path, "Enter filename: ");
	else
		path = argv[1];

    // Start reading in the file
	cout << "Reading file: " << path << endl;
    len = read_file(path, buff);
    if (len <= 0)
    {
        cout << "Error reading file: " << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }
    cout << "Bytes read: " << len << endl;

    // Insert tests here
    if (!test_parse(buff))
        exit(EXIT_FAILURE);

    // Delete the path and the copied file contents
    if (path != argv[1])
        delete [] path;
    path = nullptr;
    delete [] buff;
    buff = nullptr;

	WINPAUSE
    return 0;
}
