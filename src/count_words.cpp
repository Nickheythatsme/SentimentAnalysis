//
// Created by Nick Grout on 1/24/18.
//

#include "count_words.h"

// DEFAULT CONSTRUCTOR
count_words::count_words() noexcept :
    map<string, uint>(),
    parser()
{

}

// CONSTRUCTOR
count_words::count_words(const string &text) noexcept :
    map<string, uint>(),
    parser(text)
{
    _count_words();
}

// CONSTRUCTOR
count_words::count_words(const std::vector<string> &words) noexcept :
    map<string, uint>(),
    parser(words)
{
    _count_words();
}

// COPY CONSTRUCTOR
count_words::count_words(const count_words &obj) noexcept :
    map<string, uint>(obj),
    parser(obj.parser)
{
}

/*
 * Ostream integration, using the extraction operator.
 * Returns a ref to the ostream object
 */
std::ostream &operator<<(std::ostream &out, const count_words &obj)
{
    for (auto const &a : obj) {
        out << "\"" << a.first << "\":" << a.second << std::endl;
    }
    return out;
}

// Return the top x% and bottom y% words
std::map<string,uint> count_words::top_bottom(double top_per, double bottom_per)
{
    auto sorted_words = sort();
    std::map<string,uint> no_use_words;

    auto top_size    = long(sorted_words.size() * top_per);
    auto bottom_size = long(sorted_words.size() * bottom_per);

    // TODO this isn't working.
    auto a = sorted_words.rbegin();
    for(auto i = top_size; a != sorted_words.rend() && i < sorted_words.size(); ++i,++a)
        no_use_words.insert(*a);

    auto b = sorted_words.begin();
    for(auto i = 0; b != sorted_words.end() && i < bottom_size; ++i,++b)
        no_use_words.insert(*b);

    return no_use_words;
}

// Sort the words based on their frequencies
std::list<std::pair<string,uint>> count_words::sort() const
{
    std::list<std::pair<string,uint>> sorted_words;

    for (auto const &a : *this){
        sorted_words.push_back(a);
    }
    sorted_words.sort(compare_word_freq);

    return sorted_words;
}

// Commence the frequency counting for the word_map
void count_words::_count_words()
{
    for (auto const &a : parser) {
        this ->operator[](a) += 1;
    }
}


// Compare the frequency of one word to another word
// Sorting with this function meas the
// MOST frequent words first
// LEAST frequent words last
bool count_words::compare_word_freq(const std::pair<string,uint> &w1, const std::pair<string,uint> &w2)
{
    return w1.second > w2.second;
}
