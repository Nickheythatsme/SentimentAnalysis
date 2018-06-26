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

// Shortname for vector of window pointers paired with a counter
// Represents all words that are associated with this word, as well as 
// the strength of the association (number of times they appear next to each other)
using word_assoc = std::pair<std::shared_ptr<window>, size_t>;

class window : public std::string
{
public:
	window();
	window(const window &rhs);
	window(window &&rhs);
	~window();

	// Add a word if it doesn't exist. 
	// If it does, increment the correspondence count 
	window& add(std::shared_ptr<window> rhs);

	// Return a reference to a window by matching a string
	const word_assoc& operator[](const string &rhs) const;

	// Implementation of find/exists functions. 
	// Returns the index of the desired window iff it exists.
	// Returns NPOS if it does not exist
	size_t find(const string &rhs) const;
protected:
private:
	std::vector<word_assoc> words;
};

#endif // SENTIMENTANALYSIS_WINDOW_