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
};

// Move constructor
template<class T>
holder<T>::holder(holder<T> &&obj)
{
    data_count = obj.data_count.fetch();
    obj.data_count = 0;
    data = new T[B_SIZE];
    for (int i = 0; i < data_count; ++i)
        data[i] = std::move(obj.data[i]);
};

// Destructor
template<class T>
holder<T>::~holder()
{
    delete [] data;
};

// Push another T obj into the array.
template<class T>
bool holder<T>::push(T &&rhs)
{
    if (data_count == B_SIZE) return false;
    data[data_count++] = std::move(rhs);
    sort_points();
    return true;
}

// Push another copy of an object into the array.
template<class T>
bool holder<T>::push(const T &rhs)
{
    return this->push(T(rhs));
}

template<class T>
void holder<T>::sort_points()
{
    int i=0, j=0;

    /* Nested for loops are gross but so is the bubble sort */
    for(; i < data_count; ++i) {
        j = i;
        for(; j < data_count; ++j) {
            if(data[j] < data[i])
                std::swap(data[j],data[i]);
        }
    }

    // TODO remove when not debugging
    for (size_t i = 0; i < data_count; ++i)
        cout << data[i].first << endl;
    cout << endl;
}