#include "matrix.h"

matrix& matrix::operator*=(double x)
{
    for (auto &v : *this)
        for (auto &d : v)
            d *= x;
    return *this;
}
matrix& matrix::operator/=(double x)
{
    for (auto &v : *this)
        for (auto &d : v)
            d /= x;
    return *this;
}
matrix& matrix::operator+=(double x)
{
    for (auto &v : *this)
        for (auto &d : v)
            d += x;
    return *this;
}
matrix& matrix::operator-=(double x)
{
    for (auto &v : *this)
        for (auto &d : v)
            d -= x;
    return *this;
}

/*
Fill the matrix with random variables between MAX and MIN, to the sizes specified by x, y
*/
void matrix::fill_random(size_t x, size_t y)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(MIN, MAX);

    for (size_t i=0; i<x; ++i)
    {
        std::vector<std::vector<double>>::emplace_back(std::vector<double>());
    }
    for (auto &c : *this)
    {
        for (size_t i=0; i<y; ++i)
        c.emplace_back(distribution(generator));
    }
}

std::ostream& operator<<(std::ostream &out, const matrix &rhs)
{
    for (auto &v : rhs)
    {
        for (auto &d : v)
            out << std::setw(7) << d << "|";
        out << std::endl;
    }
    return out;
}
