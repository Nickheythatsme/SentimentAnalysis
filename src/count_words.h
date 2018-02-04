//
// Created by Nick Grout on 1/24/18.
//
#ifndef SENTIMENTANALYSIS_COUNT_WORDS_H
#define SENTIMENTANALYSIS_COUNT_WORDS_H

#include "parse.h"
#include <map>
#include <ostream>
#include <list>

class count_words: public parse
{
public:
    count_words();
    count_words(const count_words &obj);
    explicit count_words(const string &text);
    ~count_words() override = default;

    // Assignment operator
    count_words &operator=(const count_words &obj);

    // Add words from another count_words to this count_words
    friend count_words &operator+=(count_words &dest, count_words &src);

    // Output all the words and their frequencies to the ostream
    friend std::ostream &operator<<(std::ostream &out, const count_words &obj);

    // Return the number of words
    size_t size() const;

    // Return the top x% and bottom y% words
    std::map<string, unsigned long> no_use_words(double top_per, double bottom_per);

protected:
    // Sort the words based on their frequencies
    std::list<std::pair<string,unsigned long>> sort_words() const;

    // Compare the frequency of one word to another word
    static bool compare_word_freq(const std::pair<string,unsigned long> &w1, const std::pair<string,unsigned long> &w2);
private:
    // Commence the frequency counting for the word_map
    void _count_words();

    std::map<string, unsigned long> word_map;
};


#endif //SENTIMENTANALYSIS_COUNT_WORDS_H
