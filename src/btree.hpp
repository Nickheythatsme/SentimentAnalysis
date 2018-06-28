/*
6/28/18 Nicholas Grout
This class manages a templated btree, where items are stored based on their
key. Each key must implement the relational operators in order to work with 
this class.
*/
#define DEBUG
#ifndef SENTIMENT_ANALYSIS_BTREE
#define SENTIMENT_ANALYSIS_BTREE

// Used to define the number of data points in a node. Children are always data points + 1
#define BSIZE 5

#include <utility>
#include <memory>

#ifdef DEBUG
#include <iostream>
#endif

// Used to store data, with a key and a data value
template<class K, class D>
using key_data = std::pair<K, D>;

// Forward declaration
template<class K, class D>
class holder;

// split_holder is used to split the holder. We need to create a new node, as well as
// push up data to our parent node/the tree class. This struct is returned by the 
// holder's split function.
template<class K, class D>
struct split_holder 
{
	std::unique_ptr<key_data<K,D>> push_up;
	std::unique_ptr<holder<K,D>> new_rhs;
};

template<class K, class D>
class holder
{
public:
	holder();
	holder(key_data<K,D> rhs);
	holder(holder &&rhs);
	holder(const holder &rhs);
	~holder() = default;

	// Compare to_compare to they keys in our holder.
	// Returns the index of the first data which is greater than to_compare
	size_t compare(const K &to_compare);

	// Push data into the holder. 
	// Returns TRUE if success, FALSE if we're full and it's not added.
	bool push(key_data<K,D> rhs);

	// Split the node 
	// TODO add definition
	split_holder<K,D> split(key_data<K,D> new_data);

	// Return TRUE if we're full. FALSE if we're not.
	bool full() const;
protected:
private:
	static int cmp(const void* lhs, const void* rhs);
	std::unique_ptr<key_data<K,D>[]> data;
	size_t data_count;
};


template<class K, class D>
inline holder<K, D>::holder() : 
	data_count(0),
	data(new key_data<K,D>[BSIZE])
{
}

template<class K, class D>
inline holder<K, D>::holder(key_data<K,D> rhs) :
	data_count(1),
	data(new key_data<K,D>[BSIZE])
{
	data[0] = std::move(rhs);
}

template<class K, class D>
inline holder<K, D>::holder(holder && rhs) :
	data(std::move(rhs.data)),
	data_count(rhs.data_count)
{
	rhs.data = nullptr;
	rhs.data_count = 0;
}

template<class K, class D>
inline holder<K, D>::holder(const holder &rhs) :
	data(),
	data_count(new key_data<K,D>[BSIZE])
{
	data = new key_data<K,D>[BSIZE];
	for (size_t i = 0; i < data_count; ++i)
	{
		data[i] = rhs.data[i];
	}
}

// Compare to_compare to they keys in our holder.
// Returns the index of the first data which is greater than to_compare
template<class K, class D>
inline size_t holder<K, D>::compare(const K & to_compare)
{
	size_t i;
	for (i = 0; i < data_count; ++i)
	{
		if (to_compare <= to_compare)
			return i;
	}

	return i;
}

// Push data into the holder. Data_count should also increase.
template<class K, class D>
inline bool holder<K, D>::push(key_data<K,D> rhs)
{
	if (data_count == BSIZE) return false;
	data[data_count++] = std::move(rhs);
	return true;
}

// Split the holder. 
template<class K, class D>
split_holder<K,D> holder<K, D>::split(key_data<K,D> new_data)
{
	// Array of size BSIZE+1 to hold our data + 1 more data
	std::unique_ptr<key_data<K, D>[]> to_sort{ new key_data<K,D>[BSIZE + 1] }; 
	// Struct to hold new split data (the new rhs holder and push up data)
	split_holder<K,D> split_dest; 

	size_t i;
	for (i = 0; i < BSIZE; ++i)
	{
		to_sort[i] = std::move(data[i]);
	}
	to_sort[i] = std::move(new_data);

	std::qsort(
		to_sort.get(), 
		BSIZE + 1, 
		sizeof(key_data<K, D>), 
		[](const void* lhs_v, const void* rhs_v) 
		{
			key_data<K, D> lhs = *static_cast<const key_data<K, D>*>(lhs_v);
			key_data<K, D> rhs = *static_cast<const key_data<K, D>*>(rhs_v);

			if (lhs.first < rhs.first) return - 1;
			if (lhs.first > rhs.first) return 1;
			return 0;
		}
	);
#ifdef DEBUG
	for (size_t j = 0; j <BSIZE+1; ++j)
	{
		auto tracker = to_sort[j];
		std::cout << tracker.first << std::endl;
	}
#endif
	// TODO test logic here...
	split_dest.push_up.reset(new key_data<K, D>(std::move(to_sort[BSIZE / 2])));
	split_dest.new_rhs.reset(new holder<K, D>());
	for (i = BSIZE / 2 + 1; i < BSIZE + 1; ++i)
	{
		split_dest.new_rhs->push(std::move(to_sort[i]));
	}
	this->data.reset(new key_data<K, D>[BSIZE]);
	for (i = 0; i < BSIZE / 2; ++i)
	{
		this->push(std::move(to_sort[i]));
	}
	return split_dest;
}
/*
struct split_holder 
{
	std::unique_ptr<key_data<K,D>> push_up;
	std::unique_ptr<holder<K,D>> new_rhs;
};
*/

template<class K, class D>
inline bool holder<K, D>::full() const
{
	return data_count != BSIZE;
}

template<class K, class D>
int holder<K, D>::cmp(const void* lhs, const void* rhs)
{
	return 1;
}

#endif // SENTIMENT_ANALYSIS_BTREE
