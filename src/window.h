/*
6/26/2018 Nicholas Grout

This class manages the windows for one word, 
as well as the words found in association with this word.
Acts very similar to a vertex/edges in a undirected graph.
*/
#pragma once

#ifndef SENTIMENTANALYSIS_WINDOW_
#define SENTIMENTANALYSIS_WINDOW_

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

class window
{
public:
	window();
	window(const window &rhs);
	window(window &&rhs);
	~window();

	// Add a word if it doesn't exist. 
	// If it does, increment the correspondence count 
	window& add(string_ptr rhs);

	// Return a reference to a window by matching a string
	const std::string& operator[](size_t to_return) const;

	// Vector functions for iteration
	std::vector<string>::iterator begin() { return words.begin(); }
	std::vector<string>::iterator end() { return words.end(); }
	size_t size() { return words.size(); }

	// Implementation of find/exists functions. 
	// Returns the index of the desired window iff it exists.
	// Returns NPOS if it does not exist
	size_t find_word(const std::string &rhs) const;
protected:
private:
	std::vector<string_ptr> words;
};

#endif // SENTIMENTANALYSIS_WINDOW_