#include "make_window.h"
char make_window::SENTENCE_DELIMS[] = ".,?!";

// CONSTRUCTOR
make_window::make_window() :
    std::vector<window>(),
    counter()
{
}

// CONSTRUCTOR with arguments
make_window::make_window(const string &text) :
    std::vector<window>(),
    counter(text)
{
    no_use_words = counter.top_bottom(TOP_PER,BOTTOM_PER);
    _make_windows(text); 
}

// CONSTRUCTOR with arguments
make_window::make_window(const std::vector<string> &words) :
    std::vector<window>(),
    counter(words)
{
    no_use_words = counter.top_bottom(TOP_PER,BOTTOM_PER);
    for( auto const &a : words)
        _make_windows(a); 
}

// COPY CONSTRUCTOR
make_window::make_window(const make_window &obj) :
    std::vector<window>(obj),
    counter(obj.counter)
{
}

// DESTRUCTOR
make_window::~make_window()
{
}

/* Set the no_use_words that should be excluded from the window making */
void make_window::set_no_use_words(const std::map<string, uint>& new_words)
{
    no_use_words = new_words;
}

/* Make windows from the included text */
make_window& make_window::operator()(const string &text)
{
    this -> clear();
    count_words counter(text);
    no_use_words = counter.top_bottom(TOP_PER, BOTTOM_PER);
    _make_windows(text);
}

/* Make the windows from the text, and add it to the map */
void make_window::_make_windows(const string &text)
{
    std::cout << "no use words: " << std::endl;
    for( auto const &a : no_use_words )
        std::cout << a.first << '\t' << a.second << std::endl;

    parse sentence_parser(text, SENTENCE_DELIMS);
    window temp_window;

    for(auto &a : sentence_parser)
    {
        parse word_parser(a);
        for(auto &b : word_parser)
        {
            if( !no_use_words.count(b) )
                temp_window += b;
        }
        if( temp_window.size() > 2 )
        {
            this -> emplace_back(temp_window);
        }
        temp_window.clear();
    }
}
