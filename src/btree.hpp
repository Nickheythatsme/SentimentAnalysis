/*
6/28/18 Nicholas Grout
This class manages a templated btree, where items are stored based on their
key. Each key must implement the relational operators in order to work with 
this class.
*/
#ifndef SENTIMENT_ANALYSIS_BTREE
#define SENTIMENT_ANALYSIS_BTREE

#include "holder.hpp"

// Shorthand for children
template<class K, class D>
class node;
template<class K, class D>
using child_ptr_ptr = std::unique_ptr< std::unique_ptr<node<K,D>> []>;

// Used to split a node, used when we need to split a node into two, along with 'push up' data
template<class K, class D>
struct split_node
{
	std::unique_ptr<key_data<K,D>> push_up;
	std::unique_ptr<node<K,D>> new_rhs;
};

template<class K, class D>
class node : public holder<K,D>
{
    public:
        node();
        node(key_data<K,D> &&new_data);
		node(holder<K, D> to_hold);
        node(const node<K,D> &rhs);
        node(node<K,D> &&rhs);
        ~node();
        // Insert a new key_data point into this node or its subtree
        // Returns pointer to the new root
        node<K,D>* insert(key_data<K,D> &&new_data);
        key_data<K,D>& find(const K &to_find);
        bool is_leaf() const;
    protected:
    private:
        // Recursively find a spot to insert a node, splitting after insertion and
        // returning true if we have split. So when this function returns TRUE,
        // that means the current node must absorb incoming nodes/data from its child
        bool insert(key_data<K,D> &&new_data, split_node<K,D> &to_absorb);

        // Absorb a split_node into this node/holder
        bool absorb(split_node<K,D> &to_absorb, size_t child_num);
        bool split(key_data<K,D> &&new_data, split_node<K,D> &split_dest);

        // Array of pointers to child nodes
        child_ptr_ptr<K,D> children;
};

// CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node() :
    holder<K,D>(),
    children(new std::unique_ptr<node<K,D>>[BSIZE+1])
{
}

// CONSTRUCTOR with arguments
template<class K, class D>
inline node<K,D>::node(key_data<K,D> &&new_data) :
    holder<K,D>(std::move(new_data)),
    children(new std::unique_ptr<node<K,D>>[BSIZE+1])
{
}

// CONSTRUCTOR with arguments
// COPY CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node(holder<K, D> to_hold) :
    holder<K,D>(std::move(to_hold)),
    children(new std::unique_ptr<node<K,D>>[BSIZE+1])
{
}

// COPY CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node(const node<K,D> &rhs) :
    holder<K,D>(rhs),
    children(new std::unique_ptr<node<K,D>>[BSIZE+1])
{
    size_t d_count = this->get_data_count()+1;
	for (size_t i = 0; i < d_count; ++i)
	{
		children[i].reset(new node<K,D>(*rhs.children[i]));
	}
}

// MOVE CONSTRUCTOR
template<class K, class D>
inline node<K,D>::node(node<K,D> &&rhs) :
    holder<K,D>(std::move(rhs)),
    children(std::move(rhs.children))
{
}

// DESTRUCTOR
template<class K, class D>
inline node<K,D>::~node()
{
}

// Insert, returns pointer to the new root
template<class K, class D>
node<K,D>* node<K,D>::insert(key_data<K,D> &&new_data)
{
    // Make an empty holder for the splitting/absorbing
    split_node<K,D> to_absorb;
    if (insert(std::move(new_data), to_absorb))
    {
        // Handle absorbtion
        auto must_absorb = absorb(to_absorb, this->first_greater(new_data.first));
        if (must_absorb)
        {
            auto new_root = new node<K,D>(std::move(*to_absorb.push_up.release()));
            new_root->children[0].reset(this);
            // TODO fix the absorb return value. We may need another struct which contains a ptr to a node
            // new_root->children[1].reset(new node<K,D>(*(to_absorb.new_rhs.release())));
            return new_root;
        }
    }
    return this;
}

// Recursively traverse the tree and insert at the first leaf w/o children.
// Returns TRUE if our parent has data to absorb, FALSE if otherwise
template<class K, class D>
bool node<K,D>::insert(key_data<K,D> &&new_data, split_node<K,D> &to_absorb)
{
    // If we're a leaf, insert here
    if (is_leaf())
    {
        // If we have room, insert here.
        if (!this->is_full())
        {
            this->push(std::move(new_data));
            return false;
        }

        // If we don't have room, split and insert here
        else
        {
            this->split(std::move(new_data), to_absorb);
            return true;
        }
    }

    // If we're not a leaf, then compare and traverse to the next child
    auto next_child = this->first_greater(new_data.first);
    auto result = children[next_child]->insert(std::move(new_data), to_absorb);

    // If our child split, then we must absorb and return true if our parent must absorb.
    if (result)
    {
        return absorb(to_absorb, next_child);
    }
    return false;
}

// Absorb a new rhs node and push up data. Returns a new root node with its 
// own push up data if it was unable to absorb to_absorb without splitting 
// itself.
template<class K, class D>
bool node<K,D>::absorb(split_node<K,D> &to_absorb, size_t child_num)
{
	// TODO finish absorb
	return false;

    bool parent_must_absorb { false };
    if (this->is_full())
    {
        // TODO handle case
        parent_must_absorb = true;
    }
    else
    {
		this->push(key_data<K, D>(*to_absorb.push_up.release()));
		auto dcount = this->get_data_count();

		// Shift children from child_num to end one index down
		for (size_t i = dcount; i >= child_num; --i)
		{
			children[i].reset(children[i - 1].release());
		}
    }
    return parent_must_absorb;
}

template<class K, class D>
bool node<K,D>::split(key_data<K,D> &&new_data, split_node<K,D> &split_dest)
{
    split_holder<K,D> to_hold;
    holder<K, D>::split(std::move(new_data), to_hold);
	split_dest.new_rhs.reset(new node<K, D>(*to_hold.new_rhs.release()));

	// TODO Handle split
	for (size_t i = 0; i < this->get_data_count() + 1; ++i)
	{
	}

    return false;
}

// Return TRUE if we have no children. 
// Since children are filled in children[0] first, we only need to test that index
template<class K, class D>
inline bool node<K,D>::is_leaf() const
{
    return nullptr == children[0];
}

#endif // SENTIMENT_ANALYSIS_BTREE
