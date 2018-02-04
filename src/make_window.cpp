#include "make_window.h"
make_window::make_window()
{

}
make_window::make_window(const string &text)
{

}
make_window::make_window(const make_window &obj)
{

}
make_window::~make_window()
{

}

const std::vector<window> &make_window::operator()()
{
    return std::vector<window>();
}

const std::vector<window> &make_window::operator()(const string &text)
{
    return windows;
}
