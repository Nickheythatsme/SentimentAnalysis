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

// Debug flag which displays the results of splits, etc
#define _DEBUG

template<typename K, typename D>
using d_point = std::pair<K,D>;

// Forward declaration of holder class
template<typename K, typename D>
class holder;

// In a b_tree we need to be able to split and push up the middle data point.
// This struct aids that
template<typename K, typename D>
struct split_variables
{
    holder<K,D> *lesser_child;
    holder<K,D> *greater_child;
    d_point<K,D> middle_data;
};

/*
 * Holder class which holds data points. Each data point is a pair,
 * the first of the pair being the key and the second being the object itself.
 * This class sorts and manages it's data/children
 */
template<typename K, typename D>
class holder
{
public:
    // Constructors/Destructor
    holder();
    explicit holder(const d_point<K,D>& rhs);
    explicit holder(d_point<K,D> &&rhs);
    holder(const holder<K,D>&obj);
    holder(holder<K,D> &&obj);
    ~holder();

    // Assignment operator for another holder object
    holder<K,D>& operator=(const holder<K,D> &rhs);
    // Assignment operator to move an object
    holder<K,D>& operator=(holder<K,D> &&rhs);

    // Push another data point into this node
    bool push(d_point<K,D> &&obj);
    bool push(const d_point<K,D> &obj);

    // Return true if B_SIZE == data_count (we're full)
    bool full() const {return data_count == B_SIZE;}

    // Compare an incoming data point to the data in our array. 
    // Return the index of the first data_point which is greater than to_test
    size_t compare(const d_point<K,D> &&to_test) const;

    // Set data_count to 0
    void clear();

    // Split thsi node, returning a split_varaibles struct with the split nodes
    split_variables<K,D> split(d_point<K,D> &&data);

    // B_SIZE, how many data points can a node hold?
    static const size_t B_SIZE {3};
protected:
    // Find an data point which matches obj, then return it.
    d_point<K,D>& find(const d_point<K,D> &obj) const;
private:
    // Data storing points
    d_point<K,D> *data;
    // How many data points are currently stored?
    // std::atomic<size_t> data_count {0};
    size_t data_count {0};
    // Sort the currently store points
    static void sort_points(d_point<K,D> *data, size_t len);
};


#include "holder.cpp"
#endif //SENTIMENTANALYSIS_HOLDER_H
