#include <map>
#include <string>
#include <mutex>
#include <atomic>
#include <vector>

using std::string;

#ifndef VECTORIZE_COUNT_WORDS_
#define VECTORIZE_COUNT_WORDS_

using p_vector=std::vector<std::pair<std::string,unsigned long>>;

class count_words
{
    public:
        count_words();
        count_words(const count_words &obj);
        count_words(count_words&& rhs);
        ~count_words();
    protected:
    private:
        p_vector word_count;
};

#endif // VECTORIZE_COUNT_WORDS_


