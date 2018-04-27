//
// Created by nick on 11/17/2017.
//
/*
 * This class just handles a single data point. It's a lot easier to handle keys and data when they're one object
 * so that's why we need this class. It essentially just uses operators and not much else
 */

#include <ostream>

#ifndef PROJECT_DATUM_H
#define PROJECT_DATUM_H


template<class KEY,class DATA>
class datum;

/* Relational operators */
template<class KEY,class DATA>
bool operator<(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
template<class KEY,class DATA>
bool operator<(const datum<KEY,DATA> &obj1, const KEY &obj2);

template<class KEY,class DATA>
bool operator<=(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
template<class KEY,class DATA>
bool operator<=(const datum<KEY,DATA> &obj1, const KEY &obj2);

template<class KEY,class DATA>
bool operator==(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
template<class KEY,class DATA>
bool operator==(const datum<KEY,DATA> &obj1, const KEY &obj2);

template<class KEY,class DATA>
bool operator>=(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
template<class KEY,class DATA>
bool operator>=(const datum<KEY,DATA> &obj1, const KEY &obj2);

template<class KEY,class DATA>
bool operator>(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
template<class KEY,class DATA>
bool operator>(const datum<KEY,DATA> &obj1, const KEY &obj2);

template<class KEY,class DATA>
std::ostream& operator<<(std::ostream& out, const datum<KEY,DATA> obj);

/* Assignment operators */

template<class KEY,class DATA>
class datum
{
    public:
        datum() = default;
        datum(const KEY &new_key, const DATA &new_data);
        datum(const datum &obj) = default;
        ~datum() = default;
        std::ostream &display(std::ostream &out);
        /* Assignment operators */
        datum<KEY,DATA>& operator=(const datum<KEY,DATA> &obj2);
        /* Relational operators */
        friend bool operator< <>(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
        friend bool operator< <>(const datum<KEY,DATA> &obj1, const KEY &obj2);

        friend bool operator<= <>(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
        friend bool operator<= <>(const datum<KEY,DATA> &obj1, const KEY &obj2);

        friend bool operator== <>(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
        friend bool operator== <>(const datum<KEY,DATA> &obj1, const KEY &obj2);

        friend bool operator>= <>(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
        friend bool operator>= <>(const datum<KEY,DATA> &obj1, const KEY &obj2);

        friend bool operator> <>(const datum<KEY,DATA> &obj1, const datum<KEY,DATA> &obj2);
        friend bool operator> <>(const datum<KEY,DATA> &obj1, const KEY &obj2);
        /* Extraction operator for ostream output */
        // TODO remove when we're finished with building tree
        friend std::ostream& operator<< <>(std::ostream& out, const datum<KEY,DATA> obj);
        /* Getter because we can't have assignment operators for other data types */
        void get_data(DATA& to_return) const;
        void get_key(KEY& to_return) const;
        void set_key(const KEY &new_key);
        void set_data(const DATA &new_data);
    protected:
    private:
        DATA data;
        KEY key;
};

#include "datum.cpp"

#endif //PROJECT_DATUM_H
