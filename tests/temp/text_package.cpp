#include "text_package.h"


/*
 * Read the whole contents of a file to the char*
 * Returns
 * 0 or less than 0 if error
 * greater than 0 if success
 */
long read_file(const string &filename, string &buff)
{
    std::ifstream fin(filename.c_str());
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
        buff.reserve(len);
    }
    catch(std::bad_alloc &alloc){
        std::cerr << "Cannot allocate buffer for size: " << len << endl
                  << "Error: " << alloc.what() << endl;
        return -1;
    }

    // Read in file
    while(fin.good())
        buff += fin.get();
    fin.close();

    return (long)len;
}


// This is used to wrap a bunch of text files
text_package::text_package(const string &_dirname) : 
    dirname(_dirname)
{
    load_files();
}

// Wrapper for the load file function
size_t text_package::load_files()
{
    glob_t *globbed = new glob_t;
    glob(dirname.c_str(), GLOB_NOSORT, nullptr, globbed);
    load_files(globbed);
}

size_t text_package::load_files(glob_t *globbed)
{
    string buff;

    for (int i=0; i < globbed->gl_pathc; ++i)
    {
        auto temp_bytes = read_file(globbed->gl_pathv[i], buff);
        if (temp_bytes <= 0) 
            cerr<<"Error loading file: " << globbed->gl_pathv[i] << endl;
        else _bytes += temp_bytes;
        emplace_back(buff);
        buff.clear();
    }
    return _bytes;
}

text_package::~text_package()
{
}