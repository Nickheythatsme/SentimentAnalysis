#include <vector>
#include <random>
#include <iostream>
#include <iomanip>

#ifndef TEST_MATRIX
#define TEST_MATRIX

#define MAX 1000000.0
#define MIN 0.0

class matrix : public std::vector<std::vector<double>>
{
    public:
        matrix() = default;
        matrix(const matrix &rhs) = default;
        matrix(matrix &&rhs) = default;
        ~matrix() = default;
        matrix& operator*=(double x);
        matrix& operator/=(double x);
        matrix& operator+=(double x);
        matrix& operator-=(double x);

        void fill_random(size_t x, size_t y);
        friend std::ostream& operator<<(std::ostream &out, const matrix &rhs);
    protected:
    private:
};

#endif // TEST_MATRIX