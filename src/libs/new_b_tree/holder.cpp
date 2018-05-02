//
// Created by njgro on 4/27/2018.
//

#include "holder.h"

// Constructor
template<typename K, typename D>
holder<K,D>::holder()
{
    data = new d_point<K,D>[B_SIZE];
};

// Constructor with arguments
template<typename K, typename D>
holder<K,D>::holder(const d_point<K,D> &rhs) :
    data_count(1)
{
    data = new d_point<K,D>[B_SIZE];
    data[0] = rhs;
}
// Move constructor of ONE data point
template<typename K, typename D>
holder<K,D>::holder(d_point<K,D> &&rhs) :
    data_count(1)
{
    data = new d_point<K,D>[B_SIZE];
    data[0] = std::move(rhs);
}

// Copy constructor
template<typename K, typename D>
holder<K,D>::holder(const holder<K,D> &obj) :
    data_count(obj.data_count)
{
    data = new d_point<K,D>[B_SIZE];
    for (int i = 0; i < data_count; ++i)
        data[i] = obj.data[i];
}

// Move constructor of another holder object
template<typename K, typename D>
holder<K,D>::holder(holder<K,D> &&obj)
{
    data = obj.data;
    obj.data = new d_point<K,D>[B_SIZE];
    data_count = obj.data_count;
    obj.data_count = 0;
}

// Destructor
template<typename K, typename D>
holder<K,D>::~holder()
{
    delete [] data;
};

// Assignment operator
template<typename K, typename D>
holder<K,D>& holder<K,D>::operator=(const holder<K,D> &rhs)
{
    delete [] data;
    data = new d_point<K,D>[B_SIZE];
    data_count = rhs.data_count;
    for (int i=0; i < data_count; ++i)
        data[i] = rhs.data;
}

// Assignment move operator
template<typename K, typename D>
holder<K,D>& holder<K,D>::operator=(holder<K,D> &&rhs)
{
    delete [] data;
    data = rhs.data;
    rhs.data = new d_point<K,D>[B_SIZE];
    data_count = rhs.data_count;
    rhs.data_count = 0;
}

// Push another d_point<K,D> obj into the array.
template<typename K, typename D>
bool holder<K,D>::push(d_point<K,D> && rhs)
{
    if (data_count == B_SIZE) return false;
    data[data_count++] = std::move(rhs);
    sort_points(data, data_count);
    return true;
}

// Push another copy of an object into the array.
template<typename K, typename D>
bool holder<K,D>::push(const d_point<K,D> &rhs)
{
    return this->push(d_point<K,D>(rhs));
}

// Compare the data in this array to to_test.
// RETURNS the index of the first data which is greater than or equal to_test.
template<typename K, typename D>
size_t holder<K,D>::compare(const d_point<K,D> &&to_test) const
{
    size_t i=0;
    for (;i<data_count; ++i)
        if (data[i] >= to_test)
            return i;
    return i;
}

// Sort an array of d_point objects
template<typename K, typename D>
void holder<K,D>::sort_points(d_point<K,D> *data, size_t len)
{
    int i=0, j=0;

    /* Nested for loops are gross but so is the bubble sort */
    for(; i < len; ++i) {
        j = i;
        for(; j < len; ++j) {
            if(data[j].first < data[i].first)
                data[j].swap(data[i]);
        }
    }
}

// Clear every data point in the array (by setting data_count==0
template<typename K, typename D>
void holder<K,D>::clear()
{
    data_count = 0;
}

// Split this holder into two, based on the sorted data
template<typename K, typename D>
split_variables<K,D> holder<K,D>::split(d_point<K,D> &&new_t)
{
    // Make a new array one size larger than B_SIZE
    auto all_data = new d_point<K,D>[B_SIZE+1];

    // Copy our data into it, plus the new_t object
    int i=0;
    for (; i < B_SIZE; ++i)
        all_data[i] = std::move(data[i]);
    all_data[i] = std::move(new_t);

    // Sort the new array
    holder<K,D>::sort_points(all_data, B_SIZE+1);

    // Create the split_vars object
    split_variables<K,D> split_vars;
    split_vars.middle_data = std::move(all_data[(B_SIZE)/2]);
    split_vars.greater_child = new holder<K,D>();
    split_vars.lesser_child = this;
    split_vars.lesser_child->data_count = 0;

    for (i=0; i<B_SIZE/2; ++i)
        split_vars.lesser_child->push(std::move(all_data[i]));
    // i is @ the middle index here, we need to go to the end
    for (++i; i < B_SIZE+1; ++i)
        split_vars.greater_child->push(std::move(all_data[i]));

#ifdef DEBUG
        // Display the results of the split
        cout << "Lesser child data: ";
        for (int i=0; i < split_vars.lesser_child->data_count; ++i)
            cout << "("
                << split_vars.lesser_child -> data[i].first << ", "
                << split_vars.lesser_child -> data[i].first << "), ";

        cout << endl << "Middle data point: (" 
             << split_vars.middle_data.first << ", "
             << split_vars.middle_data.first << ")"
             << endl;

        cout << "Greater child data: ";
        for (int i=0; i < split_vars.greater_child->data_count; ++i)
            cout << "("
                << split_vars.greater_child -> data[i].first << ", "
                << split_vars.greater_child -> data[i].first << "), ";
        cout << endl << endl;
#endif // DEBUG

    return split_vars;
}
