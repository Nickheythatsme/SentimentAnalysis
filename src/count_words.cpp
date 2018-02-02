//
// Created by Nick Grout on 1/24/18.
//

#include "count_words.h"

// DEFAULT CONSTRUCTOR
count_words::count_words()
    :
    parse()
{

}

// CONSTRUCTOR
count_words::count_words(const string &text)
    :
    parse(text)
{

}

// COPY CONSTRUCTOR
count_words::count_words(const count_words &obj)
    :
    parse(obj)
{

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
 * counts all the parsed words. ALSO causes parse class to parse all remaining text in the queue.
 * Return number of distinct words in the queue
 */
size_t count_words::size()
{
    // Parse the rest of the words in the queue
    auto word_list = parse_words();

    for (auto const &a : word_list) {
        word_map[a] += 1;
    }
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
std::list<string> count_words::top_bottom_words(double top_per, double bottom_per)
{
    auto top_size    = long( word_map.size() * top_per);
    auto bottom_size = long( word_map.size() * bottom_per);

    auto sorted_words = sort_words();
    for(auto &a : sorted_words){
        std::cout << a << '\t' << word_map[a] << std:: endl;
    }

    return sorted_words;
}

// Sort the words based on their frequencies
std::list<string> count_words::sort_words() const
{
    std::list<string> sorted_words;

    for (auto a : word_map){
        sorted_words.push_back(a.first);
    }
    //TODO fix sorting by frequency
    //sorted_words.sort(compare_word_freq);
}

// Compare the frequency of one word to another word
bool count_words::compare_word_freq(const string &w1, const string &w2)
{
    return word_map[w1] < word_map[w2];
}
