//
// Created by njgro on 3/7/2018.
//

#include "support.h"

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
long read_file(const char *filename, char *&buff)
{
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Error opening file: " << filename << endl;
        return -1;
    }

    // Determine file size
    fin.seekg (0, fin.end);
    auto len = fin.tellg();
    fin.seekg (0, fin.beg);

    // Allocate buffer
    try {
        buff = new char[len + 1];
    }
    catch(std::bad_alloc &alloc){
        std::cerr << "Cannot allocate buffer for size: " << len << endl
                  << "Error: " << alloc.what() << endl;
        return -1;
    }

    // Read in file
    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');
    fin.close();

    return (long)len;
}
