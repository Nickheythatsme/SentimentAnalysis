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
    auto len = (long) fin.tellg();
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

/*
 * Test the object to see if it can be copied successfully
 */
template <class T> bool test_copy(T &object)
{
    try{
        {
            T copier(object);
        }
    }
    catch(std::bad_alloc &alloc){
        cerr << "Error while copying: " << alloc.what() << endl;
        return false;
    }
    catch(...){
        cerr << "Unknown error while copying object" << endl;
        return false;
    }
    return true;
}

/*
 * Test the object to see if it can be moved successfully
 */
template <class T> bool test_move(T &object)
{
    try{
        {
            T copy(object);
            T stealer(std::move(copy));
        }
    }
    catch(std::bad_alloc &alloc){
        cerr << "Error while moving: " << alloc.what() << endl;
        return false;
    }
    catch(...){
        cerr << "Unknown error while moving object" << endl;
        return false;
    }
    return true;
}

/*
 * Test the object to see if it can be assigned successfully
 */
template <class T> bool test_assignment(T &object)
{
    try{
        {
            T copy(object);
            T assigner;
            copy = assigner;
        }
    }
    catch(std::bad_alloc &alloc){
        cerr << "Error while assigning: " << alloc.what() << endl;
        return false;
    }
    catch(...){
        cerr << "Unknown error while assigning object" << endl;
        return false;
    }
    return true;
}

/*
 * Call the general testing fucntions
 */
template <class T> bool test_object(T &object)
{
    if (!test_copy<T>(object))
    {
        cerr << "Error copying object" << endl;
        return false;
    }

    if (!test_move<T>(object))
    {
        cerr << "Error moving object" << endl;
        return false;
    }

    if (!test_assignment<T>(object))
    {
        cerr << "Error assigning object" << endl;
        return false;
    }
    return true;
}

