//
// Created by njgro on 4/27/2018.
//

/* An extremely light word class for handling individual words.
 * Supports comparision, length, copy, assignment
 */
#include <cstdlib>

#ifndef SENTIMENTANALYSIS_WORD_H
#define SENTIMENTANALYSIS_WORD_H

namespace vec {

class word
{
public:
    word();
    word(const char *rhs);
    word(const word &obj);
    word(word &&obj);
    ~word();
    // returns -1 if we're less, 0 if equal, 1 if we're greater
    int compare(const word &obj) const;
    word& operator=(const word& rhs);
    word& operator=(const char* rhs);
protected:
private:
    char *data;
    size_t len;
};

}; // namespace vec


#endif //SENTIMENTANALYSIS_WORD_H
