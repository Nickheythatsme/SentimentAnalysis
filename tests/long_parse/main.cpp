#include <fstream>
#include <iostream>
#include "test_parse.h"

int main(int argc, char *argv[])
{
	char *path;

    // Assign the path
	if (argc < 2) {
        path = argv[1];
        get_path(path, "Enter filename: ");
    }
	else {
        path = new char[strlen(argv[1]) + 1];
        strcpy(path, argv[1]);
    }

    /* Insert tests here */
    if (!test_parse(path))
    {
        cout << "Error parsing words for file" << path << endl;
        WINPAUSE;
        exit(EXIT_FAILURE);
    }
    /* End of tests */

    // Delete the path and the copied file contents
    delete [] path;
    path = nullptr;

	WINPAUSE
    return 0;
}
