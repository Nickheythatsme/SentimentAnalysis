#include "parse.h"

#ifndef MAKE_WINDOW_
#define MAKE_WINDOW_

class make_window: public parse
{
public:
    make_window();
    make_window(const make_window &obj);
    ~make_window();
    virtual void add_text(const string &text) override;
protected:
private:
};

#endif //MAKE_WINDOW
