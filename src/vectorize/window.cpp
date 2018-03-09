#include "window.h"

window::window() :
    s_vector()
{
    std::cout << "Constructor!" << std::endl;

}
window::window(const window &obj) :
    s_vector(obj)
{
    std::cout << "Copy Constructor!" << std::endl;
}
window::window(window &&rhs) :
    s_vector(std::move(rhs))
{
    std::cout << "Move Constructor!" << std::endl;
}
window operator+(const window &lhs, const std::string &rhs)
{
    window win(lhs);
    win += rhs;
    return win;
}
window operator+(const window &lhs, const window &rhs)
{
    window win(lhs);
    win += rhs;
    return win;
}
window &window::operator+=(const std::string &obj)
{
    this->s_vector::emplace_back(obj);
    return *this;
}
window &window::operator+=(const window &obj)
{
    for (auto const &a : obj)
        this->s_vector::emplace_back(a);
    return *this;
}
window& window::operator+=(window &&rhs)
{
    for(auto &a : rhs)
        this->emplace_back(std::move(a));
    rhs.clear();
    return *this;
}
window &window::operator=(const window &obj)
{
    this->s_vector::operator=(obj);
    return *this;
}
window &window::operator=(window &&rhs) noexcept
{
    this->s_vector::operator=(std::move(rhs));
    return *this;
}


/*
 * Implementation for operators
 */
window& window::append(const std::string &obj)
{
    this->s_vector::emplace_back(obj);
    return *this;
}

window& window::assign(const window &obj)
{
    this->s_vector::operator=(obj);
    return *this;
}


// Output to ostream
std::ostream& window::display(std::ostream& out) const
{
    for (auto const &a : *this)
    {
        out << a << ", ";
    }
    return out;
}
