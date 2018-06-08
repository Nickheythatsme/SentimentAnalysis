#include "text_package.h"

/* text_package_error implementation */
// CONSTRUCTOR
text_package_error::text_package_error() noexcept:
    std::exception()
{
}

// CONSTRUCTOR
text_package_error::text_package_error(string _message, string _dirname, string _filename) noexcept :
    std::exception(),
    message(std::move(_message)),
    dirname(std::move(_dirname)),
    filename(std::move(_filename))
{
}
std::ostream& operator<<(std::ostream& out, const text_package_error &rhs)
{
    out << "Packaging text error: " << rhs.message << std::endl
        << "\tdirectory: " << rhs.dirname << std::endl
        << "\tfilename: " << rhs.filename << std::endl;
    return out;
}

/*
 * Read the whole contents of a file to the char*
 * Returns
 * 0 or less than 0 if error
 * greater than 0 if success
 */
long text_package::read_file(const string &filename, string &buff)
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
        std::cerr << "Cannot allocate buffer for size: " << len << std::endl
                  << "Error: " << alloc.what() << std::endl;
        throw text_package_error("Unable to make buffer size that large","",filename);
    }

    // Read in file
    while(fin.good())
        buff += fin.get();
    fin.close();

    return (long)len;
}


// This is used to wrap a bunch of text files
text_package::text_package(string dirname) : 
    _bytes(0)
{
    load_files(dirname);
}

// Wrapper for the load file function
size_t text_package::load_files(const string &dirname)
{
    auto *globbed = new glob_t;
    glob(dirname.c_str(), GLOB_NOSORT, nullptr, globbed);
    if (globbed->gl_pathc == 0)
        throw text_package_error("No files found.", dirname, "NULL");
    load_files(globbed);
    return globbed->gl_pathc;
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
            std::cerr<<"Error loading file: " << globbed->gl_pathv[i] << std::endl;
        }
        else emplace_back(buff);
        buff.clear();
    }
    return _bytes;
}