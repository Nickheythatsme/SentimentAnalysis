//
// Created by Nick Grout on 1/24/18.
//

#include "count_words.h"

// DEFAULT CONSTRUCTOR
count_words::count_words() :
    parse()
{

}

// CONSTRUCTOR
count_words::count_words(const string &text) :
    parse(text)
{

}

// COPY CONSTRUCTOR
count_words::count_words(const count_words &obj) :
    parse(obj)
{

}

count_words& operator+=(count_words &dest, count_words &src)
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
size_t count_words::count()
{
    // Parse the rest of the words in the queue
    auto word_list = parse_words();

    for(auto const &a : word_list){
        word_map[a] += 1;
    }
    return word_map.size();
}

/*
 * Ostream integration, using the extraction operator.
 * Returns a ref to the ostream object
 */
std::ostream& operator<<(std::ostream& out, const count_words &obj)
{
    for(auto const &a : obj.word_map){
        out << "\"" << a.first << "\":" << a.second << std::endl;
    }
    return out;
}
