/*
6/28/18 Nicholas Grout
This class manages a templated btree, where items are stored based on their
key. Each key must implement the relational operators in order to work with 
this class.
*/
// #define DEBUG
#ifndef SENTIMENT_ANALYSIS_BTREE
#define SENTIMENT_ANALYSIS_BTREE

// Used to define the number of data points in a node. Children are always data points + 1
#define BSIZE 5

#include <utility>
#include <memory>
#include <algorithm>
#include <iterator>

#ifdef DEBUG
#include <iostream>
#endif

// Used to store data, with a key and a data value
template<class K, class D>
using key_data = std::pair<K, D>;

// Abbreviation of compare function. This is used to sort data in the array
template<class K>
using Compare = bool(*)(const K &lhs, const K &rhs);

// Default compare function used for sorting the arrays
template<class K>
bool default_compare(const K &lhs, const K &rhs)
{
	return lhs < rhs;
}

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
#ifdef DEBUG
public:
#else
protected:
#endif
	holder();
	explicit holder(key_data<K,D> rhs);
	holder(holder &&rhs);
	holder(const holder &rhs);
	virtual ~holder() = default;

	// Compare to_compare to they keys in our holder.
	// Returns the index of the first data which is greater than to_compare
	size_t first_greater(const K &to_compare);

	// Push data into the holder. 
	// Returns TRUE if success, FALSE if we're full and it's not added.
	bool push(key_data<K,D> rhs);

	// Split the node 
    // Returns a split_holder with a 
	virtual split_holder<K,D> split(key_data<K,D> new_data);

	// Return TRUE if we're full. FALSE if we're not.
	bool is_full() const;

    // Sorting functions. All static to simplify the splitting (since splitting requires BSIZE+1)
    static void sort(key_data<K,D>* to_sort, size_t len);
	static bool is_sorted(const key_data<K,D>* to_check, size_t len);
	static Compare<K> compare; // Used to compare during the sort

    // Data this nodes holds, and the data count
	std::unique_ptr<key_data<K,D>[]> data;
	size_t data_count;
};

// Set compare to default compare function
template<class K, class D>
Compare<K> holder<K,D>::compare = default_compare<K>;

// CONSTRUCTOR
template<class K, class D>
inline holder<K, D>::holder() : 
	data_count(0),
	data(new key_data<K,D>[BSIZE])
{
}

// CONSTRUCTOR with arguments
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
inline size_t holder<K, D>::first_greater(const K & to_compare)
{
	size_t i;
	for (i = 0; i < data_count; ++i)
	{
		if (!compare(data[i].first, to_compare)) // same as: to_compare <= data[i].first
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
    if (!is_sorted(data.get(), data_count))
        sort(data.get(), data_count);
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

    // Sort the new array
    sort(to_sort.get(), BSIZE+1);

    // get the push up data
	split_dest.push_up.reset(new key_data<K, D>(std::move(to_sort[BSIZE / 2])));
	split_dest.new_rhs.reset(new holder<K, D>());
    // move data > push up data into the new rhs holder
	for (i = BSIZE / 2 + 1; i < BSIZE + 1; ++i)
	{
		split_dest.new_rhs->push(std::move(to_sort[i]));
	}
    // move data < push up data into this holder
	this->data.reset(new key_data<K, D>[BSIZE]);
    this->data_count = 0;
	for (i = 0; i < BSIZE / 2; ++i)
	{
		this->push(std::move(to_sort[i]));
	}

#ifdef DEBUG
    std::cout << std::endl << "self: ";
	for (i=0; i < this->data_count; ++i)
    {
        std::cout << this->data[i].first << ", ";
    }

    std::cout << std::endl << 
        "Push up data: " << split_dest.push_up->first << std::endl;

    std::cout << "rhs: ";
	for (i=0; i < split_dest.new_rhs->data_count; ++i)
	{
		std::cout << split_dest.new_rhs->data[i].first << ", ";
	}
    std::cout << std::endl;
#endif

	return split_dest;
}

template<class K, class D>
inline bool holder<K, D>::is_full() const
{
	return data_count != BSIZE;
}

template<class K, class D>
inline bool holder<K, D>::is_sorted(const key_data<K,D>* data, size_t len)
{
	for (size_t i = 0; i < len-1; ++i)
	{
        if (!compare(data[i].first, data[i + 1].first))
            return false;
	}
	return true;
}

// TODO implement quicksort? This bubble sort is lame.
template<class K, class D>
void holder<K,D>::sort(key_data<K,D>* data, size_t len)
{
	for (size_t i = 0; i < len - 1; ++i)
    {
        if (!compare(data[i].first, data[i + 1].first))
        {
            std::swap(data[i], data[i+1]);
        }
    }
    if (!is_sorted(data, len))
    {
        sort(data, len);
    }
}

/***********************/
/* NODE Implementation */

// Shorthand for children
template<class K, class D>
class node;
template<class K, class D>
using child_ptr = std::unique_ptr<node<K,D>[]>;

template<class K, class D>
class node : public holder<K,D>
{
    public:
        node();
        node(const node<K,D> &rhs);
        node(node<K,D> &&rhs);
        ~node();
        // Insert a new key_data point into this node or its subtree
        // Returns pointer to the new root
        node<K,D>* insert(key_data<K,D> new_data);
        key_data<K,D>& find(const K &to_find);
        bool is_leaf() const;
    protected:
    private:
        // Recursively find a spot to insert a node, splitting after insertion and
        // returning true if we have split. So when this function returns TRUE,
        // that means the current node must absorb incoming nodes/data from its child
        bool insert(key_data<K,D> new_data, split_holder<K,D> &to_absorb);

        // Absorb a split_holder into this node/holder
        node<K,D>* absorb(key_data<K,D> new_data, split_holder<K,D> &to_absorb);

        // Array of pointers to child nodes
        child_ptr<K,D> children;
        size_t child_count;
};

// CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node() :
    holder<K,D>(),
    children(new node<K,D>[BSIZE+1]),
    child_count(0)
{
}

// COPY CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node(const node<K,D> &rhs) :
    holder<K,D>(rhs),
    children(new node<K,D>[BSIZE+1]),
    child_count(0)
{
}

// MOVE CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node(node<K,D> &&rhs) :
    holder<K,D>(std::move(rhs)),
    children(std::move(rhs.children)),
    child_count(0)
{
}

// DESTRUCTOR
template<class K, class D>
inline node<K,D>::~node()
{
}

// Insert, returns pointer to the new root
template<class K, class D>
node<K,D>* node<K,D>::insert(key_data<K,D> new_data)
{
    // Make an empty holder for the splitting/absorbing
    split_holder<K,D> to_absorb;
    if (insert(std::move(new_data), to_absorb))
    {
        // TODO handle absorbtion
        auto new_root = absorb(std::move(new_data), to_absorb);
        return new_root;
    }
    return this;
}

template<class K, class D>
bool node<K,D>::insert(key_data<K,D> new_data, split_holder<K,D> &to_absorb)
{
    // If we're a leaf and have room, insert here
    if (is_leaf())
    {
        if (!this->is_full())
        {
            this->push(std::move(new_data));
            return nullptr;
        }
        else
        {
            this->split(std::move(new_data), to_absorb);
        }
    }
    return false;
}

// Absorb a new rhs node and push up data. Returns a new root node with its 
// own push up data if it was unable to absorb to_absorb without splitting 
// itself.
template<class K, class D>
node<K,D>* node<K,D>::absorb(key_data<K,D> new_data, split_holder<K,D> &to_absorb)
{
    //TODO finish absorb
    return true;
}

template<class K, class D>
inline bool node<K,D>::is_leaf() const
{
    return child_count == 0;
}

#endif // SENTIMENT_ANALYSIS_BTREE
