#include "window.h"
#include "parse.h"
#include "../support.h"
#include <fstream>
#include <vector>

bool test_window(const std::vector<std::string> &words)
{
    window window1;
    for (auto const &a : words)
        window1 += a;

    for (auto &a : window1)
        cout << a << endl;

    return true;
}


/*
 * Parse the words and return the vector of parsed words
 */
parse parse_words(const char *buff)
{
    char delims[] = " \n\t.,€";
    parse parser {delims};
    parser(buff);
    return parser;
}

int main(int argc, char *argv[])
{
	char *path;
    char *buff;

    // Assign the path
	if (argc < 2)
        get_path(path, "Enter filename: ");
	else {
        path = new char[strlen(argv[1]) + 1];
        strcpy(path, argv[1]);
    }

    // Start reading in the file
	cout << "Reading file: " << path << endl;
    auto len = read_file(path, buff);
    if (len <= 0)
    {
        cout << "Error reading file: " << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }
    cout << "Bytes read: " << len << endl;

    // Parse the words in the file
    parse words {parse_words(buff)};
    if (words.size() <= 1) {
        cout << "Error parsing words for file" << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }

    // Insert tests here
    if (!test_window(words)){
        cout << "Error making window from words." << endl
             << "Filename: " << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }
    // End of tests

    // Delete the path and the copied file contents
    delete [] path;
    path = nullptr;
    delete [] buff;
    buff = nullptr;

	WINPAUSE
    return 0;
}
