#include "bnode.h"

template<typename K, typename D>
size_t bnode<K, D>::CHILD_SIZE = data_holder<K, D>::B_SIZE + 1;

// CONSTRUCTOR
template<typename K, typename D>
inline bnode<K, D>::bnode() :
	holder<K,D>(),
	children(new bnode<K,D>[CHILD_SIZE])
{
}

// COPY CONSTRUCTOR
template<typename K, typename D>
inline bnode<K, D>::bnode(const bnode & rhs) :
	holder<K,D>(rhs),
	children(CHILD_SIZE)
{
	for (size_t i = 0; i < CHILD_SIZE; ++i)
		children[i] = rhs.children[i];
}

// MOVE CONSTRUCTOR
template<typename K, typename D>
inline bnode<K, D>::bnode(bnode && rhs) :
	holder<K,D>(std::move(rhs)),
	children(std::move(rhs.children))
{
}

template<typename K, typename D>
inline bnode<K, D>::~bnode()
{
}

template<typename K, typename D>
inline bnode<K, D>& bnode<K, D>::operator=(const bnode<K, D>& rhs)
{
	children.reset();
	for (size_t i = 0; i < CHILD_SIZE; ++i)
	{
		children[i] = rhs.children[i];
	}
}

template<typename K, typename D>
inline bnode<K, D>& bnode<K, D>::operator=(bnode<K, D>&& rhs)
{
	children.reset();
	children = std::move(rhs.children);
}

template<typename K, typename D>
inline bool bnode<K, D>::is_leaf()
{
	for (size_t i=0; i<CHILD_SIZE;++i)
		if (children[i])
}
