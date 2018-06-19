/*
 * 6/8/2018 Nicholas Grout
 *
 * This class maintains the children of this node. It is inherited from a holder
 * so it also holds data. This class only traverses, inserts, and deletes on 
 * itself or its children. There is no parent pointer.
 */

#ifndef SENTIMENTANALYSIS_BNODE_
#define SENTIMENTANALYSIS_BNODE_

#include "holder.h"
#include <memory>

// Forward declaration of bnode class
template<typename K, typename D>
class bnode;

// Unique pointer to children array
template<typename K, typename D>
using children_ptr = std::unique_ptr<bnode<K,D>[]>;

// bnode class. Manages the children and traversal/insertion.
template<typename K, typename D>
class bnode : public holder<K,D>
{
    public:
        bnode();
        bnode(const bnode &rhs);
        bnode(bnode &&rhs);
        ~bnode();
        bnode<K,D>& operator=(const bnode<K,D>& rhs);
        bnode<K,D>& operator=(bnode<K,D>&& rhs);

		// Return true if this is a leaf, false if otherwise
        bool is_leaf();

		// Wrapper for the insert. This function returns a pointer to the root, 
		// whether that be this node or a new node
		bnode* insert(d_point<K, D>&& to_insert);
		static size_t CHILD_SIZE;
    protected:
    private:
        // Resolve an incoming split TODO we may need to split again ourselves.
        bool resolve_split(split_variables<K,D> &incoming);

        // Call split on our selves. Oragnize our children and seperate them.
        virtual split_variables<K,D> split(d_point<K,D>&& data);

        // Recursive insert function. Returns a pointer to the split struct if it exists, nullptr otherwise
		std::unique_ptr<split_variables<K, D>> insert(d_point<K, D>&& to_insert);

        // Go to the next child depending on the data 'to_insert'
        bnode<K,D>* next_child(d_point<K,D>&& to_insert);

		// Unique ptr to children
		children_ptr<K,D> children;
};

#include "bnode.cpp"
#endif // SENTIMENTANALYSIS_BNODE_
