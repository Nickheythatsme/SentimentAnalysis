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

    friend window operator+(const window &win, const std::string &obj);
    friend window operator+(const window &win, const window &obj);
    window& operator+=(const std::string &obj);
    window& operator+=(const window &obj);
    window& operator+=(window &&rhs);

    window& operator=(const window &obj);
    window& operator=(window &&rhs) noexcept;

protected:
private:
};

#endif //SENTIMENTANALYSIS_VECTORIZE_WINDOW
