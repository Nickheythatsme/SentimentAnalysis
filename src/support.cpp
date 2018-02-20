#include "support.h"

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
// Lower all letters in a word to lowercase
void lower(string &word)
{
    for(auto &c : word)
        if ( c >= 65 && c <= 90 )
            c += 32;
}

// Replace the HTML from the str with periods
void replace_html(string &str)
{
    for (auto a = 0lu; a < to_clean_count; ++a)
    {
        auto pos = str.find(to_clean[a]);
        if( pos != string::npos )
        {
            auto len = strlen(to_clean[a]) + pos;
            for (auto i = pos; i < len; ++i)
            {
                str[i] = '.';
            }
            replace_html(str);
        }
    }
}

// Remove the non-ascii characters
void replace_non_ascii(string &str)
{
    for (auto & a : str)
    {
        if (a < 32 || a > 126)
            a = ' ';
    }
}

// Clean the HTML from the aclImdb text data
void clean(string &word)
{
    lower(word);
    replace_html(word);
    replace_non_ascii(word);
}
