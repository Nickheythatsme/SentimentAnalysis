#include "support.h"

// HTML tags that should be cleaned
static const char *to_clean[2] = {"<br />","<br >"};

/*
 * Read the entirety of a file into to_return
 * returns 0 if failure/nothing read.
 * Or the filesize if success
 */
string read_file(char *fname)
{
    std::ifstream in(fname);
    auto fsize = in.tellg();
    char *buff;
    if(!in) return string();

    // Get file length
    fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = in.tellg() - fsize;
    in.seekg(0, std::ios::beg);

    // Allocate the buffer
    buff = new char[long(fsize)+1];
    in.read(buff, fsize);

    return string(buff);
}

std::vector<string> glob_files(const char *dir_name)
{
    glob_t globbed;
    std::vector<string> files;

    // Change into desired working directory
    auto old_dir = chdir(dir_name);

    // Glob all *.txt files 
    glob("*.txt", GLOB_NOSORT, NULL, &globbed);

    // Change back to old dir
    fchdir(old_dir);

    for(auto i = 0lu; i < globbed.gl_pathc; ++i)
        files.emplace_back(read_file(globbed.gl_pathv[i]));
    return files;
}

// Replace the HTML from the str
void replace(string &str)
{
}

// Clean the HTML from the aclImdb text data
void clean_files(std::vector<string> &words)
{
    for(auto &a : words)
    {
        replace(a);
    }
}
