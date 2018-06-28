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

window& window::add(string_ptr rhs)
{
	words.emplace_back(std::move(rhs));
	return *this;
}

// Returns the word 
const std::string& window::operator[](size_t to_return) const
{
	return words[to_return];
}

// Find a word. Returns std::string::npos if word is not in this list
size_t window::find_word(const std::string & rhs) const
{
	size_t location = 0;
	for (const auto &word : words)
	{
		if (word == to_find)
			return location;
		++location;
	}
	return std::string::npos;
}
