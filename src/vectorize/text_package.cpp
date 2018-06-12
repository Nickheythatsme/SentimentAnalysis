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
    start_loading(globbed);
    globfree(globbed);

    return this->size();
}

size_t text_package::start_loading(glob_t *globbed)
{
    // Make an array of the number of files we have
    std::vector<string> texts {globbed->gl_pathc};
    size_t thread_count = std::thread::hardware_concurrency(); // TODO replace with global config file
    std::cout << "Loading files on " << thread_count << " threads" << std::endl;
    size_t bytes_read[thread_count];
    std::thread threads[thread_count];

    size_t increment = globbed->gl_pathc / thread_count;
    size_t i;
    for (i=0; i<thread_count-1; ++i)
    {
        threads[i] = std::thread(
                &text_package::_load_files,
                *this, 
                globbed, 
                std::ref(texts), 
                std::ref(bytes_read[i]),
                i*increment, 
                i*increment + increment);
    }
    threads[i] = std::thread(
            &text_package::_load_files,
            *this,
            globbed,
            std::ref(texts),
            std::ref(bytes_read[i]),
            i*increment,
            globbed->gl_pathc);

    for (i=0; i<thread_count; ++i)
    {
        threads[i].join();
        _bytes += bytes_read[i];
    }
    for (auto &c : texts)
        std::vector<string>::push_back(std::move(c));
    return std::vector<string>::size();
}

// Implmentation of the load files. Uses the filenames from glob and reads/loads files
void text_package::_load_files(glob_t *globbed, 
        std::vector<string> texts, 
        size_t &bytes,
        size_t start, size_t end)
{
    string buff;
    bytes = 0;

    for (int i=start; i < end; ++i)
    {
        auto temp_bytes = read_file(globbed->gl_pathv[i], buff);
        bytes += temp_bytes;
        if (temp_bytes <= 0) {
            std::cerr<<"Error loading file: " << globbed->gl_pathv[i] << std::endl;
        }
        else 
            texts[i] = std::move(buff);
        buff.clear();
    }
}
