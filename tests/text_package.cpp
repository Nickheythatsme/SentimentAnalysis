#include "text_package.h"

/* text_package_error implementation */
text_package_error::text_package_error(const string &_message, const string &_dirname, const string &_filename) :
    message(_message),
    dirname(_dirname),
    filename(_filename)
{
}
std::ostream& operator<<(std::ostream& out, const text_package_error &rhs)
{
    out << "Packaging text error: " << rhs.message << endl
        << "\tdirectory: " << rhs.dirname << endl
        << "\tfilename: " << rhs.filename << endl;
    return out;
}

/*
 * Read the whole contents of a file to the char*
 * Returns
 * 0 or less than 0 if error
 * greater than 0 if success
 */
long read_file(const string &filename, string &buff)
{
    std::ifstream fin(filename.c_str());
    if (!fin) 
        throw text_package_error("error opening file", "", filename);

    // Determine file size
    fin.seekg (0, fin.end);
    auto len = (long) fin.tellg();
    fin.seekg (0, fin.beg);

    // Allocate buffer
    try {
        buff.reserve(len);
    }
    catch(std::bad_alloc &alloc) {
        std::cerr << "Cannot allocate buffer for size: " << len << endl
                  << "Error: " << alloc.what() << endl;
        throw text_package_error("Unable to make buffer size that large","",filename);
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
    if (globbed->gl_pathc == 0)
        throw text_package_error("No files found.", dirname, "NULL");
    load_files(globbed);
}

// Implmentation of the load files. Uses the filenames from glob and reads/loads files
size_t text_package::load_files(glob_t *globbed)
{
    string buff;

    for (int i=0; i < globbed->gl_pathc; ++i)
    {
        auto temp_bytes = read_file(globbed->gl_pathv[i], buff);
        _bytes += temp_bytes;
        if (temp_bytes <= 0) {
            cerr<<"Error loading file: " << globbed->gl_pathv[i] << endl;
        }
        else emplace_back(buff);
        buff.clear();
    }
    return _bytes;
}

text_package::~text_package()
{
}