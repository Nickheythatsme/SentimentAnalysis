//
// Created by nick on 11/17/2017.
//

#include "datum.h"

/* CONSTRUCTOR with arguments */
template<class KEY,class DATA>
datum<KEY,DATA>::datum(const KEY &new_key, const DATA &new_data)
{
    key = new_key;
    data = new_data;
}
template<class KEY,class DATA>
std::ostream &datum<KEY,DATA>::display(std::ostream &out)
{
    out << key;
    return out;
}

/* ASSIGNMENT OPERATOR */
template<class KEY,class DATA>
datum<KEY,DATA>& datum<KEY,DATA>::operator= (const datum<KEY,DATA> &obj)
{
    key = obj.key;
    data = obj.data;
    return *this;
}

/* RELATIONAL OPERATORS */
template<class KEY,class DATA>
bool operator< (const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2)
{
    return (obj1.key - obj2.key) < 0;
}

template<class KEY,class DATA>
bool operator< (const datum<KEY,DATA> &obj1, const KEY &obj2)
{
    return (obj1.key - obj2) < 0;
}

template<class KEY,class DATA>
bool operator<= (const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2)
{
    return (obj1.key - obj2.key) <= 0;
}

template<class KEY,class DATA>
bool operator<= (const datum<KEY,DATA> &obj1, const KEY &obj2)
{
    return (obj1.key - obj2) <= 0;
}

template<class KEY,class DATA>
bool operator== (const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2)
{
    return (obj1.key - obj2.key) == 0;
}

template<class KEY,class DATA>
bool operator== (const datum<KEY,DATA> &obj1, const KEY &obj2)
{
    return (obj1.key - obj2) == 0;
}

template<class KEY,class DATA>
bool operator>= (const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2)
{
    return (obj1.key - obj2.key) >= 0;
}

template<class KEY,class DATA>
bool operator>= (const datum<KEY,DATA> &obj1, const KEY &obj2)
{
    return (obj1.key - obj2) >= 0;
}

template<class KEY,class DATA>
bool operator> (const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2)
{
    return (obj1.key - obj2.key) > 0;
}

template<class KEY,class DATA>
bool operator> (const datum<KEY,DATA> &obj1, const KEY &obj2)
{
    return (obj1.key - obj2) > 0;
}

/* Shift operator used for ostream */
template<class KEY,class DATA>
std::ostream& operator<< (std::ostream& out, const datum<KEY,DATA> obj)
{
    return out << obj.key;
}

/* Manually set the key */
template<class KEY,class DATA>
void datum<KEY,DATA>::set_key(const KEY &new_key)
{
    key = new_key;
}

/* Manually set the data */
template<class KEY,class DATA>
void datum<KEY,DATA>::set_data(const DATA &new_data)
{
    data = new_data;
}

/* Manually retrieve the data, since assignment operators for other data types are not allowed */
template<class KEY,class DATA>
void datum<KEY,DATA>::get_data(DATA& to_return) const
{
    to_return = data;
}

template<class KEY,class DATA>
void datum<KEY,DATA>::get_key(KEY& to_return) const
{
    to_return = key;
}
