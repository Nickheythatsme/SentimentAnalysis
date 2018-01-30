#include <iostream>
#include <fstream>
#include "src/count_words.h"

using std::cout;
using std::endl;

string text  = "this. is some text. I hope that it is formatted correctly. I know this is difficult but, I must do it!";
string text2 = "This statically specifies what build type (configuration) will be built in this build tree. Possible values are empty, Debug, Release, RelWithDebInfo and MinSizeRel.";

/*
 * Read the entirety of a file into to_return
 * returns 0 if failure/nothing read.
 * Or the filesize if success
 */
auto read_file(char *fname, string &to_return)
{
    std::ifstream in(fname);
    auto fsize = 0l;
    char *buff;
    if(!in) return fsize;

    // Get file length
    fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = in.tellg() - fsize;
    in.seekg(0, std::ios::beg);

    // Allocate the buffer
    buff = new char[fsize+1l];
    in.read(buff, fsize);

    to_return = string(buff);
    return fsize;
}

int main(int argc, char *argv[])
{
    string f;
    auto len = read_file(argv[1], f);
    cout << "bytes read: " << len << endl;
    cout << f << endl;

    count_words counter(text);
    counter.add_text(text2);
    counter.count();

    cout << counter << endl;

    return 0;
}
