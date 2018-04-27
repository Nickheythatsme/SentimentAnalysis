//
// Created by njgro on 4/27/2018.
//
#include <utility>
#include <mutex>

#ifndef SENTIMENTANALYSIS_HOLDER_H
#define SENTIMENTANALYSIS_HOLDER_H

// function used to compare two keys.
// RETURNS
//      1 if lhs > rhs
//      0 if lhs == rhs
//      -1 if lhs < rhs
template<class K, class D>
using comparison = int (*)(const K& lhs, const K& rhs);

template<class K, class D>
class holder
{
public:
    holder();
    holder(const holder<K,D> &obj);
    holder(holder<K,D> &&obj);
    ~holder();
protected:
private:
    // Data storing points
    std::pair<K,D> *data;
    // How many data points are currently stored?
    size_t data_count;
    // Sort the currently store points
    void sort_points();

    // Function to compare two keys
    static comparison comp;
    static const size_t H_SIZE {3};
};


#include "holder.cpp"
#endif //SENTIMENTANALYSIS_HOLDER_H
