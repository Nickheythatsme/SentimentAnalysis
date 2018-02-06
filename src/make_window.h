#include <map>
#include "window.h"
#include "count_words.h"

#ifndef MAKE_WINDOW_
#define MAKE_WINDOW_

class make_window : public count_words
{
public:
    make_window();
    explicit make_window(const string &text);
    make_window(const make_window &obj);
    ~make_window();
    const std::vector<window>& operator()();
    const std::vector<window>& operator()(const string &text);
protected:
private:
    /* make the windows from the text */
    std::map<string, uint> no_use_words;
    std::vector<window> windows;
};

#endif //MAKE_WINDOW
