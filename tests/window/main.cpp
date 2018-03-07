#include "window.h"
#include "parse.h"
#include "support.h"
#include <fstream>
#include <vector>


/*
 * Parse the words and return the vector of parsed words
 */
parse&& parse_words(const char *buff)
{
    char delims[] = " \n\t.,€";
    parse parser {delims};
    parser(buff);
    return std::move(parser);
}

bool test_window(const std::vector<std::string> &words)
{
// TODO add window testing here!
    auto n1 = new node(words[0]);
    n1->insert_end(words[1]);
    cout << n1->std::string::c_str() << endl;
    cout << n1->next()->std::string::c_str() << endl;
    return false;
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

    parse words {parse_words(buff)};
    if (words.size() <= 1) {
        cout << "Error parsing words for file" << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }
    cout << "HERE!" << endl;

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
