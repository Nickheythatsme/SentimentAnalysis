//
// Created by njgro on 4/27/2018.
//
#include <utility>
#include <mutex>
#include <atomic>
#include <iostream>

using std::cout;
using std::endl;

#ifndef SENTIMENTANALYSIS_HOLDER_H
#define SENTIMENTANALYSIS_HOLDER_H

template<class T>
struct split_variables
{
    holder *lower_child;
    holder *greater_child;
    T middle_data;
};

// Holder class which holds data points. Each data point is a pair,
// the first of the pair being the key and the second being the object itself.
// This class sorts and manages it's data/children
template<class T>
class holder
{
public:
    holder();
    explicit holder(const T& rhs);
    explicit holder(T &&rhs);
    holder(const holder<T>&obj);
    holder(holder<T> &&obj);
    ~holder();
    holder<T>& holder<T>::operator=(const holder<T> &rhs);
    holder<T>& holder<T>::operator=(holder<T> &&rhs);
    bool push(T &&obj);
    bool push(const T &obj);
    bool full() const {return data_count == B_SIZE;}
    size_t compare(const T &&to_test) const;
    void clear();
    split_variables split(T &&data);
protected:
private:
    // Data storing points
    T *data;
    // How many data points are currently stored?
    // std::atomic<size_t> data_count {0};
    size_t data_count {0};
    // Sort the currently store points
    static void sort_points(T *data, size_t len);

    static const size_t B_SIZE {3};
};


#include "holder.cpp"
#endif //SENTIMENTANALYSIS_HOLDER_H
