#include "bnode.h"

template<typename K, typename D>
size_t bnode<K, D>::CHILD_SIZE = data_holder<K, D>::B_SIZE + 1;

template<typename K, typename D>
inline bnode<K, D>::bnode()
{
	children = new b_node<K, D>[data_holder<K, D>::B_SIZE+1];
}
