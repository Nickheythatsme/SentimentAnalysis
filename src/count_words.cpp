//
// Created by Nick Grout on 1/24/18.
//

#include "count_words.h"

// DEFAULT CONSTRUCTOR
count_words::count_words()
    :
    parse()
{
    _count_words();

}

// CONSTRUCTOR
count_words::count_words(const string &text)
    :
    parse(text)
{
    _count_words();

}

// COPY CONSTRUCTOR
count_words::count_words(const count_words &obj)
    :
    parse(obj)
{
    word_map = obj.word_map;
}

count_words &operator+=(count_words &dest, count_words &src)
{
    return dest;
}

count_words &count_words::operator=(const count_words &obj)
{
    return *this;
}

/*
 * counts all the parsed words.
 */
size_t count_words::size() const
{
    return word_map.size();
}

/*
 * Ostream integration, using the extraction operator.
 * Returns a ref to the ostream object
 */
std::ostream &operator<<(std::ostream &out, const count_words &obj)
{
    for (auto const &a : obj.word_map) {
        out << "\"" << a.first << "\":" << a.second << std::endl;
    }
    return out;
}

// Return the top x% and bottom y% words
std::list<std::pair<string,unsigned long>> count_words::top_bottom_words(double top_per, double bottom_per)
{
    auto top_size    = long( word_map.size() * top_per);
    auto bottom_size = long( word_map.size() * bottom_per);

    auto sorted_words = sort_words();
    for(auto &a : sorted_words){
        std::cout << a.first << '\t' << a.second << std:: endl;
    }

    return sorted_words;
}

// Commence the frequency counting for the word_map
void count_words::_count_words()
{
    // Parse the rest of the words in the queue
    auto word_list = parse_words();

    for (auto const &a : word_list) {
        word_map[a] += 1;
    }
}

// Sort the words based on their frequencies
std::list<std::pair<string,unsigned long>> count_words::sort_words() const
{
    std::list<std::pair<string,unsigned long>> sorted_words;

    for (auto const &a : word_map){
        sorted_words.push_back(a);
    }
    //TODO fix sorting by frequency
    sorted_words.sort(compare_word_freq);

    return sorted_words;
}

// Compare the frequency of one word to another word
// Sorting with this function meas the
// MOST frequent words first
// LEAST frequent words last
bool count_words::compare_word_freq(const std::pair<string,unsigned long> &w1, const std::pair<string,unsigned long> &w2)
{
    return w1.second > w2.second;
}
