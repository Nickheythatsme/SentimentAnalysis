//
// Created by Nick Grout on 1/24/18.
//
#ifndef SENTIMENTANALYSIS_COUNT_WORDS_H
#define SENTIMENTANALYSIS_COUNT_WORDS_H

#include "parse.h"
#include <map>
#include <ostream>
#include <list>

class count_words: public std::map<string, uint>
{
public:
    count_words() noexcept;
    count_words(const count_words &obj) noexcept;
    explicit count_words(const string &text) noexcept;
    ~count_words() = default;

    // Assignment operator
    count_words &operator=(const count_words &obj);

    // Add words from another count_words to this count_words
    friend count_words &operator+=(count_words &dest, count_words &src);

    // Output all the words and their frequencies to the ostream
    friend std::ostream &operator<<(std::ostream &out, const count_words &obj);

    // Return the top x% and bottom y% words
    std::map<string, uint> no_use_words(double top_per, double bottom_per);

    // Sort the words based on their frequencies
    std::list<std::pair<string,uint>> sort() const;
protected:

    // Compare the frequency of one word to another word
    static bool compare_word_freq(const std::pair<string,uint> &w1, const std::pair<string,uint> &w2);
private:
    // Commence the frequency counting for the word_map
    void _count_words();

    parse parser;
};


#endif //SENTIMENTANALYSIS_COUNT_WORDS_H
