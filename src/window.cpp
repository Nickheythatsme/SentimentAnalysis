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
    win.append(rhs);
    return win;
}
window operator+(const window &lhs, const window &rhs)
{
    window win(lhs);
    return win.append(rhs);
}
window &window::operator+=(const std::string &obj)
{
    return append(obj);
}
window &window::operator+=(const window &obj)
{
    return append(obj);
}
window& window::operator+=(window &&rhs)
{
    return append(rhs);
}
window &window::operator=(const window &obj)
{
    return assign(obj);
}
window &window::operator=(window &&rhs) noexcept
{
    return assign(rhs);
}


/*
 * Implementation for operators
 */
window& window::append(const std::string &obj)
{
    this->s_vector::emplace_back(obj);
    return *this;
}

window& window::append(const window &obj)
{
    for (auto const &a: obj)
        this->emplace_back(a);
    return *this;
}

window& window::append(window &&rhs)
{
    for (auto &a : rhs)
        this->emplace_back(std::move(a));
    return *this;
}

window& window::assign(const window &obj) noexcept
{
    this->s_vector::operator=(obj);
    return *this;
}

window& window::assign(window &&rhs)
{
    this->s_vector::operator=(std::move(rhs));
    return *this;
}
