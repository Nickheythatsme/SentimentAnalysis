#include <map>
#include "window.h"
#include "count_words.h"

#ifndef MAKE_WINDOW_
#define MAKE_WINDOW_

#define TOP_PER    0.99
#define BOTTOM_PER 0.05


class make_window : public std::vector<window>
{
public:
    make_window();
    explicit make_window(const string &text);
    explicit make_window(const std::vector<string> &words);
    make_window(const make_window &obj);
    ~make_window();

    /* Make windows from the text */
    make_window& operator()(const string &text);

    /* Set the no_use_words that should be excluded from the window making */
    void set_no_use_words(const std::map<string, uint>& new_words);

protected:
private:
    /* Make the windows from the text, and add it to the map */
    void _make_windows(const string &text); 

    /* count the words to find the frequency */
    count_words counter;

    /* make the windows from the text */
    std::map<string, uint> no_use_words;
    static char SENTENCE_DELIMS[];
};

#endif //MAKE_WINDOW
