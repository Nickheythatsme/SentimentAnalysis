//
// Created by Nick Grout on 10/29/17.
//
#include "data_holder.h"

#ifdef SENTIMENTANALYSIS_B_TREE_H
#ifndef SENTIMENTANALYSIS_NODE_H
#define SENTIMENTANALYSIS_NODE_H

template<class KEY, class DATA>
class node : public data_holder<KEY, DATA>
{
    public:
        node();
        node(node<KEY, DATA> const &obj);
        explicit node(datum<KEY,DATA> const &obj);
        explicit node(data_holder<KEY, DATA> const &obj);
        ~node();
        /* Insert new data (wrapper),
         * and move root if we get a new root (not wrapper) */
        static int insert(datum<KEY,DATA> const &new_data, node<KEY, DATA> *&root);
        /* Remove all nodes in this subtree */
        void clear();
        /* Return true if we have no children */
        bool is_leaf() const;
        /* Find data recursively */
        bool static find(KEY const &to_find, const node<KEY,DATA> *root, DATA &to_return);
        std::ostream &display(std::ostream &out, int tabs);
    protected:
        /* Determine what the next child is based on the data. Returns -1 if something is wrong */
        node<KEY, DATA> *next_child(datum<KEY,DATA> const &new_data);
        node<KEY, DATA> *next_child(KEY const &to_compare) const;
        /* Recursive function for inserting new data */
        int insert(struct split_info<KEY, DATA> *&new_struct);
        /* Resolve the split from our children */
        int resolve_split(struct split_info<KEY, DATA> *&in_split);
        /* Split ourselves if we're a leaf (basic split w/o handling children */
        int split_leaf(struct split_info<KEY, DATA> *new_struct);
        /* Split ourselves if we're internal
         * (split_leaf plus additional children handling */
        int split_internal(struct split_info<KEY, DATA> *&new_struct);
        /* Manually connect a new node */
        void connect(node<KEY, DATA> *new_child, short child_index);
        void swap_max(node<KEY,DATA> *&obj1, node<KEY,DATA> *&obj2);
    private:
        node<KEY, DATA> **children; /* Array to hold our children */
};

#include "node.cpp"

#endif //SENTIMENTANALYSIS_NODE_H
#endif //SENTIMENTANALYSIS_B_TREE_H
