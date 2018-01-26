#include <iostream>
#include <map>
#include "src/parse.h"

using std::cout;
using std::endl;

string text  = "this. is some text. I hope that it is formatted correctly. I know this is difficult but, I must do it!";
string text2 = "This statically specifies what build type (configuration) will be built in this build tree. Possible values are empty, Debug, Release, RelWithDebInfo and MinSizeRel.";


int main()
{
    parse parser(text);
    parser.add_text(text2);
    auto words = parser.parsed_words();
    for(auto const &a : words)
        cout << a << endl;
    parser.add_text(text2);
    return 0;
}
