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

// Forward declaration of holder class
template<class T>
class holder;

// In a b_tree we need to be able to split and push up the middle data point.
// This struct aids that
template<class T>
struct split_variables
{
    holder<T> *lesser_child;
    holder<T> *greater_child;
    T middle_data;
};

/*
 * Holder class which holds data points. Each data point is a pair,
 * the first of the pair being the key and the second being the object itself.
 * This class sorts and manages it's data/children
 */
template<class T>
class holder
{
public:
    // Constructors/Destructor
    holder();
    explicit holder(const T& rhs);
    explicit holder(T &&rhs);
    holder(const holder<T>&obj);
    holder(holder<T> &&obj);
    ~holder();

    // Assignment operator for another holder object
    holder<T>& operator=(const holder<T> &rhs);
    // Assignment operator to move an object
    holder<T>& operator=(holder<T> &&rhs);

    // Push another data point into this node
    bool push(T &&obj);
    bool push(const T &obj);

    // Find an data point which matches obj, then return it.
    const T& find(const T &obj) const;

    // Return true if B_SIZE == data_count (we're full)
    bool full() const {return data_count == B_SIZE;}

    // Compare an incoming data point to the data in our array. 
    // Return the index of the first data_point which is greater than to_test
    size_t compare(const T &&to_test) const;

    // Set data_count to 0
    void clear();

    // Split thsi node, returning a split_varaibles struct with the split nodes
    split_variables<T> split(T &&data);

    // B_SIZE, how many data points can a node hold?
    static const size_t B_SIZE {3};
//protected:
//private:
    // Data storing points
    T *data;
    // How many data points are currently stored?
    // std::atomic<size_t> data_count {0};
    size_t data_count {0};
    // Sort the currently store points
    static void sort_points(T *data, size_t len);
};


#include "holder.cpp"
#endif //SENTIMENTANALYSIS_HOLDER_H
