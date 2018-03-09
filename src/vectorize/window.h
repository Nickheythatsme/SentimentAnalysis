#include <string>
#include <iostream>
#include <vector>

#ifndef SENTIMENTANALYSIS_VECTORIZE_WINDOW
#define SENTIMENTANALYSIS_VECTORIZE_WINDOW

using s_vector=std::vector<std::string>;

class window : public s_vector
{
public:
    window();
    window(const window &obj);
    window(window &&rhs);
    ~window() = default;

    // Addition operators
    friend window operator+(const window &win, const std::string &obj);
    friend window operator+(const window &win, const window &obj);

    //  Addition assignment operators
    window& operator+=(const std::string &obj);
    window& operator+=(const window &obj);
    window& operator+=(window &&rhs);

    // Assignment operators
    window& operator=(const window &obj);
    window& operator=(window &&rhs) noexcept;

protected:
    window& append(const std::string &obj);
    window& assign(const window &obj);

    // Display to ostream object
    std::ostream& display(std::ostream& out) const;
private:
};

#endif //SENTIMENTANALYSIS_VECTORIZE_WINDOW
