#include <iostream>
#include "src/parse.h"

using std::cout;
using std::endl;

string text = "this. is some text. I hope that is is formatted correctly. I know this is difficult but, I must do it!";


int main()
{
    auto words = parse::parse_text(text);
    for(auto c : text)
        cout << c << endl;
    for(auto a : words)
        cout << a << endl;
    return 0;
}
