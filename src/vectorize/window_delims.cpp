//
// Created by njgro on 3/9/2018.
//

#include <cstring>
#include "window_delims.h"
// CTOR
window_delims::window_delims() :
    window()
{
    sentence_delims = nullptr;
}
// CTOR with sentence delimiters
window_delims::window_delims(const char *sentence_delims)
{

}
// COPY CTOR
window_delims::window_delims(const window_delims &obj) :
    window(obj)
{
    sentence_delims = nullptr;
}
// MOVE CTOR
window_delims::window_delims(window_delims &&rhs) :
    window(std::move(rhs)),
    delims(std::move(rhs.delims))
{
    sentence_delims = rhs.sentence_delims;
    rhs.sentence_delims = nullptr;
}
// DTOR
window_delims::~window_delims()
{
    if (sentence_delims) {
        delete[] sentence_delims;
        sentence_delims = nullptr;
    }
}
// Add a word with its delimiter to this object
void window_delims::add_word(const std::string &word, const std::string &delim)
{
    window::append(word);
    delims.append(word);
}
void window_delims::set_sentence_delimiters(const char *new_delims)
{
    // TODO will this seg fault on nullptr?
    delete [] sentence_delims;
    if (new_delims) {
        sentence_delims = new char[strlen(new_delims) + 1];
        strcpy(sentence_delims, new_delims);
    } else
        sentence_delims = nullptr;

}
std::vector<window> window_delims::sentence_windows() const
{
    if (!sentence_delims)
        return std::vector<window>();
}

window window_delims::make_window(window &win, int index) const
{
    if (index > delims.size())
        return win;
    win += this->s_vector::operator[]((unsigned long)index);
    if (manip.test_character(delims[index].c_str(),sentence_delims))
        return win;
    return make_window(win, ++index);

}
std::vector<window> window_delims::full_windows(int len) const
{
    return std::vector<window>();
}
