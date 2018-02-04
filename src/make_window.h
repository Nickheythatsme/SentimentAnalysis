#include <map>
#include "parse.h"
#include "window.h"

#ifndef MAKE_WINDOW_
#define MAKE_WINDOW_

class make_window: public parse
{
public:
    make_window();
    make_window(const make_window &obj);
    ~make_window();
protected:
private:
    std::map<string,unsigned long> no_use_words;
};

#endif //MAKE_WINDOW
