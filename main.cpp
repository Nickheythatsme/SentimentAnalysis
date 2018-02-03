#include <iostream>
#include <fstream>
#include "src/count_words.h"
#include "src/window.h"
#include <glob.h>


using std::cout;
using std::endl;

static const string text  = "this. is some text. I hope that it is formatted correctly. I know this is difficult but, I must do it!";
static const string text2 = "This statically specifies what build type (configuration) will be built in this build tree. Possible values are empty, Debug, Release, RelWithDebInfo and MinSizeRel.";

void test_window(const string &text);
void test_count(const string &text);
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

auto glob_files(char *dir_name)
{
    glob_t globbed;
    glob(dir_name, GLOB_NOSORT, NULL, &globbed);
    string f;

    for(auto i = 0lu; i < globbed.gl_pathc; ++i)
        f += read_file(globbed.gl_pathv[i]);
    return f;
}

int main(int argc, char *argv[])
{
    //auto f = read_file(argv[1]);
    auto f = glob_files(argv[1]);
    cout << "bytes read: " << f.size() << endl;

    test_window(f);
    //test_count(f);
    return 0;
}

void test_window(const string &text)
{
    window w1;
    window w2;
    parse p;
    auto v = p(text);
    for (auto &a : v)
        cout << a << endl;
}


void test_count(const string &text)
{

    count_words counter(text);
    counter.size();

    auto sorted = counter.top_bottom_words(1.0,1.0);

}
