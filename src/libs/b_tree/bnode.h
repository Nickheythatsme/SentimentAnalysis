/*
 * 6/8/2018 Nicholas Grout
 *
 * This class maintains the children of this node. It is inherited from a holder
 * so it also holds data. This class only traverses, inserts, and deletes on 
 * itself or its children. There is no parent pointer.
 */
#include "holder.h"

#ifndef SENTIMENTANALYSIS_BNODE_
#define SENTIMENTANALYSIS_BNODE_

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

        bool is_leaf();
    protected:
    private:
        // Resolve an incoming split TODO we may need to split again ourselves.
        bool resolve_split(split_variables<K,D> &incoming);

        // Call split on our selves. Oragnize our children and seperate them.
        virtual split_variables<K,D> split(d_point<K,D>&& data);

        // Recursive insert function. Returns true if our child split
        bool insert(d_point<K,D>&& to_insert, split_variables<K,D> &split)

        // Go to the next child depending on the data 'to_insert'
        bnode<K,D>* next_child(d_point<K,D>&& to_insert);

        bnode<K,D> *children;
};

#endif // SENTIMENTANALYSIS_BNODE_
