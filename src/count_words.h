//
// Created by Nick Grout on 1/24/18.
//
#ifndef SENTIMENTANALYSIS_COUNT_WORDS_H
#define SENTIMENTANALYSIS_COUNT_WORDS_H

#include "parse.h"
#include <map>

class count_words : public parse
{
public:
    count_words(const count_words &obj);
    count_words(const string &text);
    count_words();
    count_words& operator+=(const count_words &obj);
    count_words& operator=(const count_words &obj);
protected:
private:
    // TODO we need functions to add parsed words to the word_map.
    // TODO we need
    std::map<string, unsigned long> word_map;
};


#endif //SENTIMENTANALYSIS_COUNT_WORDS_H
