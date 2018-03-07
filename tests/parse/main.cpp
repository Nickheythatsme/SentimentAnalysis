#include <fstream>
#include <iostream>
#include "../support.h"
#include "test_parse.h"


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

    // Insert tests here
    if (!test_parse(buff))
    {
        cout << "Error parsing words for file" << path << endl;
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
