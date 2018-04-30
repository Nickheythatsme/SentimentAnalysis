//
// Created by njgro on 4/27/2018.
//

#include <cstring>
#include "word.h"

namespace vec {

// CONSTRUCTOR
word::word() :
    data(nullptr),
    len(0)
{
}
// COPY CONSTRUCTOR
word::word(const word &obj) :
    len(obj.len)
{
    data = new char[len];
    strcpy(data,obj.data);
}
// CONSTRUCTOR with arguments
word::word(const char *rhs)
{
    len = strlen(rhs);
    data = new char[len];
    strcpy(data,rhs);
}
// MOVE constructor
word::word(word &&obj) :
    data(obj.data),
    len(obj.len)
{
    obj.data = nullptr;
    obj.len = 0;
}
// DESTRUCTOR
word::~word()
{
    if (data)
        delete [] data;
}
int word::compare(const word &obj) const
{
    const char *l = data;
    const char *r = obj.data;
    char sum;

    while(*l && *r)
    {
        sum = *l - *r;
        if (sum)
            return sum;
        ++l; ++r;
    }
    return sum;
}
word &word::operator=(const word &rhs)
{
    if (data)
        delete [] data;
    len = rhs.len;
    data = new char[len];
    strcpy(data, rhs.data);
    return *this;
}
word &word::operator=(const char *rhs)
{
    if (data)
        delete [] data;
    len = strlen(rhs);
    data = new char[len];
    strcpy(data, rhs);
    return *this;
}

}// namespace vec
