#include <iostream>
#include <memory>
#include <cstring>

using std::cout;
using std::endl;


void del(const char d[])
{
    return;
}


void del_reg(char *d)
{
    if (d)
        delete [] d;
}

void more_practice(const char *word)
{
    auto s2 = std::unique_ptr<char[]> {new char[strlen(word) + 1]};
    auto s3 = std::unique_ptr<char[], std::function<void(char*)>> {};

    strcpy(s2.get(), word);
    cout << s2.get() << endl;
    s2[0] = 'f';
    cout << s2[0] << endl;
}

int main(int argc, char **argv)
{
    auto static_char = std::unique_ptr<const char[], std::function<void(const char[])>> {"this!", [](const char d[])
        {
            return;
        }
    };

    auto static_char2 = std::unique_ptr<const char[], std::function<void(const char[])>> {"this!",del};

    auto stealer = std::unique_ptr<const char[], std::function<void(const char[])>> {std::move(static_char2)};

    more_practice("this!");

}

