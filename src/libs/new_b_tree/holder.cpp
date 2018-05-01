//
// Created by njgro on 4/27/2018.
//

#include "holder.h"

// Constructor
template<class T>
holder<T>::holder()
{
    data = new T[B_SIZE];
};

// Constructor with arguments
template<class T>
holder<T>::holder(const T &rhs) :
    data_count(1)
{
    data = new T[B_SIZE];
    data[0] = rhs;
}
// Move constructor of ONE data point
template<class T>
holder<T>::holder(T &&rhs) :
    data_count(1)
{
    data = new T[B_SIZE];
    data[0] = std::move(rhs);
}

// Copy constructor
template<class T>
holder<T>::holder(const holder<T> &obj) :
    data_count(obj.data_count)
{
    data = new T[B_SIZE];
    for (int i = 0; i < data_count; ++i)
        data[i] = obj.data[i];
}

// Move constructor of another holder object
template<class T>
holder<T>::holder(holder<T> &&obj)
{
    data_count = obj.data_count;
    obj.data_count = 0;
    data = obj.data;
    obj.data = new T[B_SIZE];
}


// Destructor
template<class T>
holder<T>::~holder()
{
    delete [] data;
};

// Assignment operator
template<class T>
holder<T>& holder<T>::operator=(const holder<T> &rhs)
{
    delete [] data;
    data = new T[B_SIZE];
    data_count = rhs.data_count;
    for (int i=0; i < data_count; ++i)
        data[i] = rhs.data;
}

// Assignment move operator
template<class T>
holder<T>& holder<T>::operator=(holder<T> &&rhs)
{
    delete [] data;
    data = rhs.data;
    rhs.data = new T[B_SIZE];
    data_count = rhs.data_count;
    rhs.data_count = 0;
}

// Push another T obj into the array.
template<class T>
bool holder<T>::push(T &&rhs)
{
    if (data_count == B_SIZE) return false;
    data[data_count++] = std::move(rhs);
    sort_points(data, data_count);
    return true;
}

// Push another copy of an object into the array.
template<class T>
bool holder<T>::push(const T &rhs)
{
    return this->push(T(rhs));
}

// Compare the data in this array to to_test.
// RETURNS the index of the first data which is greater than or equal to_test.
template<class T>
size_t holder<T>::compare(const T &&to_test) const
{
    size_t i=0;
    for (;i<data_count; ++i)
        if (data[i] >= to_test)
            return i;
    return i;
}

// Sort an array of T objects
template<class T>
void holder<T>::sort_points(T *data, size_t len)
{
    int i=0, j=0;

    /* Nested for loops are gross but so is the bubble sort */
    for(; i < len; ++i) {
        j = i;
        for(; j < len; ++j) {
            if(data[j] < data[i])
                std::swap(data[j],data[i]);
        }
    }
}

// Clear every data point in the array (by setting data_count==0
template<class T>
void holder<T>::clear()
{
    data_count = 0;
}


// Split this holder into two, based on the sorted data
template<class T>
split_variables<T> holder<T>::split(T &&new_t)
{
    // Make a new array one size larger than B_SIZE
    auto all_data = new T[B_SIZE+1];

    // Copy our data into it, plus the new_t object
    int i=0;
    for (; i < B_SIZE; ++i)
        all_data[i] = std::move(data[i]);
    all_data[i] = std::move(new_t);

    // Sort the new array
    holder<T>::sort_points(all_data, B_SIZE+1);

    // Create the split_vars object
    split_variables<T> split_vars;
    split_vars.middle_data = all_data[(B_SIZE)/2];
    split_vars.greater_child = new holder<T>();
    split_vars.lesser_child = this;
    split_vars.lesser_child.data = 0;

    for (i=0; i<B_SIZE/2; ++i)
        split_vars.lesser_child.push(std::move(all_data[i]));
    // i is @ the middle index here, we need to go to the end
    for (++i; i < B_SIZE+1; ++i)
        split_vars.greater_child.push(std::move(all_data[i]));
    return split_vars;
}
