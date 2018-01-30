//
// Created by Nick Grout on 1/24/18.
//
#ifndef SENTIMENTANALYSIS_COUNT_WORDS_H
#define SENTIMENTANALYSIS_COUNT_WORDS_H

#include "parse.h"
#include <map>
#include <ostream>

class count_words: public parse
{
public:
    count_words();
    count_words(const count_words &obj);
    explicit count_words(const string &text);
    ~count_words() override = default;
    count_words &operator=(const count_words &obj);
    friend count_words &operator+=(count_words &dest, count_words &src);
    friend std::ostream &operator<<(std::ostream &out, const count_words &obj);
    size_t count();
protected:
private:
    std::map<string, unsigned long> word_map;
};


#endif //SENTIMENTANALYSIS_COUNT_WORDS_H
