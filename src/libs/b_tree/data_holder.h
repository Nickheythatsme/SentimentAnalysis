//
// Created by Nick Grout on 10/22/17.
//
// This holds and handles the data in the node. It handles sorting, splitting,
// insertion, and compares to incoming data points 

#include <iostream>
#include "datum.h"

#define MAX_DEGREE 4
#define MAX_DATA (MAX_DEGREE - 1)

#ifndef SENTIMENTANALYSIS_B_TREE_H
#define SENTIMENTANALYSIS_B_TREE_H


/* Forward declaration */
template<class KEY, class DATA>
class node;

/* struct used for splitting and inserting data. */
template<class KEY, class DATA>
struct split_info
{
    split_info();
    ~split_info(); /* We do NOT delete new_right if it exists. Other nodes will have taken it and will delete it on their own */
    datum<KEY,DATA> new_data; /* Data incoming from the insert. Exists whether there is a split or not */
    datum<KEY,DATA> push_up_data; /* Data that is pushed up after a split */
    node<KEY, DATA> *new_right; /* The new right node */
};

template<class KEY, class DATA>
int sort(DATA *array, short len);//Bubble sort the array.

template<class KEY, class DATA>
class data_holder
{
    //TODO uncomment
    //protected:
    public:
        data_holder();
        data_holder(data_holder<KEY, DATA> const &obj);
        explicit data_holder(datum<KEY,DATA> const &new_data);
        virtual ~data_holder();
        virtual int add(datum<KEY,DATA> const &new_data);
        std::ostream &display(std::ostream &out);
        /* Split ourselves and sort out left, middle, and right data */
        virtual int split(split_info<KEY, DATA> *temp_holder);
        int is_full() const;
        int return_data_count() const;
        /* Tests if to_compare is in the array, copies to to_return if it is, then 
         * returns true or false depending on if it's in the array */
        bool find(KEY const &to_compare, DATA &to_return) const;
        /* Test to see where this data would be if it was in the array.
         * Returns the index of the first array value which is lower than the test value */
        int compare(datum<KEY,DATA> const &to_compare) const;
        int compare(KEY const &to_compare) const;
        void clear_data();//Sets data_count to 0
        bool greater_than(const data_holder<KEY,DATA> &obj) const;
    private:
        datum<KEY,DATA> *data;
        short data_count;
};


#include "data_holder.cpp"

#endif //SENTIMENTANALYSIS_B_TREE_H
