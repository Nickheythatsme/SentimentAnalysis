#include "window.h"

window::window() : 
	std::string()
{
}

window::window(const window & rhs) :
	std::string(rhs)
{
}

window::window(window && rhs) :
	std::string(std::move(rhs))
{
}

window::~window()
{
}

window & window::add(std::shared_ptr<window> rhs)
{
	auto new_pair = std::make_pair(std::move(rhs), 0);
	words.emplace_back(std::move(new_pair));
	return *this;
}

const word_assoc & window::operator[](const std::string & to_find) const
{
	return words[find(to_find)];
}

size_t window::find_word(const std::string & rhs) const
{
	return std::string::npos;
}
