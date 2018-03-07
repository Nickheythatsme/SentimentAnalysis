#include "window.h"
#include "parse.h"
#include "support.h"
#include <fstream>
#include <vector>


/*
 * Parse the words and return the vector of parsed words
 */
std::vector<std::string> parse_words(const char *buff)
{
    char delims[] = " \n\t.,€";
    parse parser {delims};
    parser(buff);
    return parser;
}

bool test_window(const std::vector<std::string> words)
{
// TODO add window testing here!
    return false;
}

int main(int argc, char *argv[])
{
	char *path;
    char *buff;

    // Assign the path
	if (argc < 2)
        get_path(path, "Enter filename: ");
	else
		path = argv[1];

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

    if (!parse_words(buff)) {
        cout << "Error parsing words for file" << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }

    // Insert tests here
    // End of tests

    // Delete the path and the copied file contents
    if (path != argv[1])
        delete [] path;
    path = nullptr;
    delete [] buff;
    buff = nullptr;

	WINPAUSE
    return 0;
}
