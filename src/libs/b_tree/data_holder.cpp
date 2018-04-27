// Created by Nick Grout on 10/22/17.
//
// This holds and handles the data in the node. It handles sorting, splitting,
// insertion, and compares to incoming data points 
//

#include "data_holder.h"

template<class KEY, class DATA>
std::ostream &data_holder<KEY,DATA>::display(std::ostream &out)
{
    int i = 0;
    out << "(";
    for(; i < data_count-1; ++i)
        out << data[i] << ", ";
    for(; i < data_count; ++i)
        out << data[i];
    out << ")";

    return out;
}

/* CONSTRUCTOR */
template<class KEY, class DATA>
data_holder<KEY, DATA>::data_holder()
{
    data = new datum<KEY,DATA>[MAX_DATA];
    data_count = 0;
}

/* CONSTRUCTOR */
template<class KEY, class DATA>
data_holder<KEY, DATA>::data_holder(datum<KEY,DATA> const &new_data)
{
    data = new datum<KEY,DATA>[MAX_DATA];
    data_count = 1;
    data[0] = new_data;
}

/* COPY CONSTRUCTOR */
template<class KEY, class DATA>
data_holder<KEY, DATA>::data_holder(data_holder<KEY, DATA> const &obj)
{
    data_count = obj.data_count;
    data = new datum<KEY,DATA>[MAX_DATA];
    for(short i = 0; i < data_count; ++i)
        data[i] = obj.data[i];
}

/* DESTRUCTOR */
template<class KEY, class DATA>
data_holder<KEY, DATA>::~data_holder()
{
    delete[] data;
    data = nullptr;
}

/* Split this node */
template<class KEY, class DATA>
int data_holder<KEY, DATA>::split(split_info<KEY, DATA> *temp_holder)
{
    short i = 0;
    short middle_item = 0;
    short last_item = MAX_DATA + 1; //index of the last item in the new array

    /* Create and sort a new array with ALL data */
    datum<KEY,DATA> *new_array = new datum<KEY,DATA>[last_item];
    for(; i < MAX_DATA; ++i)
        new_array[i] = this->data[i];
    new_array[MAX_DATA] = temp_holder->new_data; //Add the last datum
    sort(new_array, last_item);

    /* Find the middle data item */
    middle_item = MAX_DATA / 2;
    temp_holder->push_up_data = new_array[middle_item];

    /* Get the right side of the array */
    for(i = middle_item + (short)1; i < last_item; ++i)
        temp_holder->new_right->add(new_array[i]);

    /* Get the left side of the array */
    this->clear_data();
    for(i = 0; i < middle_item; ++i)
        this->add(new_array[i]);

    delete[] new_array;

    return 1;
}

/* Sets data_count to 0. It's the same as delete the array IF DATA has an
 * assignment operator! */
template<class KEY, class DATA>
void data_holder<KEY, DATA>::clear_data()
{
    data_count = 0;
    return;
}

/* Return how much room is left */
template<class KEY, class DATA>
int data_holder<KEY, DATA>::is_full() const
{
    return data_count >= MAX_DATA;
}

/* Return the number of data items in this array */
template<class KEY, class DATA>
int data_holder<KEY, DATA>::return_data_count() const
{
    return data_count;
}

/* Insert a new data item into this array. Returns 0 if we're full */
template<class KEY, class DATA>
int data_holder<KEY, DATA>::add(datum<KEY,DATA> const &new_data)
{
    if(data_count >= MAX_DATA) return 0;
    data[data_count] = new_data;
    ++data_count;
    sort(data, data_count);
    return data_count;
}

/* Test to see if data is in this node. Returns 1 if is is, 0 if it is not */
template<class KEY, class DATA>
bool data_holder<KEY,DATA>::find(KEY const &to_compare, DATA &to_return) const
{
    for(short i = 0; i < data_count; ++i)
        if(data[i] == to_compare)
        {
            data[i].get_data(to_return);
            return true;
        }
    return false;
}

template<class KEY, class DATA>
bool data_holder<KEY,DATA>::greater_than(const data_holder<KEY,DATA> &obj) const
{
    return data[0] > obj.data[0];
}

/* COMPARES to another data point.
 * Returns the index of the first data point in the array
 * that is greater than the test data point */
template<class KEY, class DATA>
int data_holder<KEY, DATA>::compare(datum<KEY,DATA> const &to_compare) const
{
    short i = 0;
    for(; i < data_count; ++i)
        if(to_compare < data[i])
            return i;
    return i;
}

template<class KEY, class DATA>
int data_holder<KEY, DATA>::compare(KEY const &to_compare) const
{
    short i = 0;
    for(; i < data_count; ++i)
        if(data[i] > to_compare)
            return i;
    return i;
}

/* Bubble sort. We don't really care much about sorting speed,
 * there are few data items per node.
 * ALSO please note this uses short as index.
 * Long arrays obviously will not work */
template<class KEY, class DATA>
int sort(datum<KEY,DATA> *array, short len)
{
    datum<KEY,DATA> temp;
    short i = 0, j = 0;

    /* Nested for loops are gross but so is the bubble sort */
    for(; i < len; ++i) {
        j = i;
        for(; j < len; ++j) {
            if(array[j] < array[i]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    return 1;
}

/* CONSTRUCTOR */
template<class KEY, class DATA>
split_info<KEY, DATA>::split_info()
{
    new_right = nullptr;
}

/* SPLIT INFO DESTRUCTOR */
template<class KEY, class DATA>
split_info<KEY, DATA>::~split_info()
{
}
