//
// Created by Nick Grout on 10/29/17.
//

#include "node.h"

template<class KEY,class DATA>
std::ostream &node<KEY,DATA>::display(std::ostream &out, int tabs)
{
    for(int i = 0; i < tabs; ++i)
        out << "  ";
    data_holder<KEY,DATA>::display(out);
    out << std::endl;

    ++tabs;
    for(int i = 0; i < MAX_DEGREE && children[i]; ++i)
        children[i] -> display(out, tabs);
    return out;
}

/* Find data recursively and return it */
template<class KEY, class DATA>
bool node<KEY,DATA>::find(KEY const &to_find, const node<KEY,DATA> *root, DATA &to_return)
{
    if( root -> data_holder<KEY,DATA>::find(to_find, to_return) )
        return true;
    if( root -> is_leaf() )
        return false;
    return find(to_find, root -> next_child(to_find), to_return);
}

//Static
template<class KEY, class DATA>
int node<KEY, DATA>::insert(datum<KEY,DATA> const &new_data, node<KEY, DATA> *&root)
{
    node<KEY, DATA> *new_root;
    split_info<KEY, DATA> *new_struct = new split_info<KEY, DATA>;
    new_struct->new_data = new_data;

    root->insert(new_struct);

    //Move our old root to the new one if it exists
    if(new_struct->new_right) {
        new_root = new node<KEY, DATA>(new_struct->push_up_data);
        new_root->connect(root, 0);
        new_root->connect(new_struct->new_right, 1);
        root = new_root;
    }
    delete new_struct;
    return 1;
}

//Recursively find the spot we're supposed to insert. Insert on the recursive calls,
//then on the return from the calls we test to see if we have an incoming split.
template<class KEY, class DATA>
int node<KEY, DATA>::insert(struct split_info<KEY, DATA> *&new_struct)
{
    if(this->is_leaf()) {
        if(this->is_full())
            return this->split_leaf(new_struct);
        else return data_holder<KEY, DATA>::add(new_struct->new_data);
    }

    /* Recursive call */
    this->next_child(new_struct->new_data)->insert(new_struct);

    if(new_struct->new_right)
        return this->resolve_split(new_struct);
    return 1;
}

//Split our node for our parent's absorption
template<class KEY, class DATA>
int node<KEY, DATA>::split_leaf(struct split_info<KEY, DATA> *new_struct)
{
    new_struct->new_right = new node<KEY, DATA>;
    data_holder<KEY, DATA>::split(new_struct);
    return 1;
}

//TODO this is the problem function
template<class KEY, class DATA>
int node<KEY, DATA>::split_internal(struct split_info<KEY, DATA> *&new_struct)
{
#ifdef NDEBUG
    std::cout << "split_internal:" << std::endl
              << "\tnew_struct->push_up_data: " << new_struct -> push_up_data << std::endl
              << "\tself before split: " << std::endl;
    this -> display(std::cout, 5);
#endif
    int child_index;
    struct split_info<KEY, DATA> *our_struct = new split_info<KEY, DATA>;
    our_struct->new_data = new_struct->push_up_data;

    /* We need to see where the children
     * will go after we split :( */
    child_index = data_holder<KEY, DATA>::compare(our_struct->new_data);

    /* First part is the same as split leaf */
    this->split_leaf(our_struct);

#ifdef NDEBUG
    std::cout << "\tself after split: " << std::endl;
    this -> display(std::cout, 5);
    std::cout << "\tchild index: " << child_index << std::endl;
#endif

    // Make sure our_struct->new_right is the maximum new right (between our_struct and new_struct)
    //swap_max(our_struct->new_right, new_struct->new_right);

#ifdef NDEBUG
    std::cout << "\tour_struct->new_right: ";
    our_struct -> new_right -> display(std::cout,0);
    std::cout << "\tnew_struct->new_right: ";
    new_struct -> new_right -> display(std::cout,0);
    std::cout << "\tnew_strut->push_up_data: " << new_struct -> push_up_data << std::endl;
#endif

    our_struct->new_right->connect(this->children[1],0);
    our_struct->new_right->connect(this->children[2],1);
    our_struct->new_right->connect(this->children[3],2);
    this->connect(new_struct->new_right,1);
    this->connect(NULL,2);
    this->connect(NULL,3);

    /*
    // Move our children to the new node
    for(int i = 1, j = 0; i < MAX_DEGREE; ++i, ++j) {
        our_struct->new_right->connect(this->children[i], j);
        this->connect(NULL, i);
    }

    this->connect(new_struct->new_right,1);
    */

    // Get rid of the old split_info
    delete new_struct;
    new_struct = our_struct;

    return 1;
}

template<class KEY, class DATA>
void node<KEY, DATA>::swap_max(node<KEY,DATA> *&obj1, node<KEY,DATA> *&obj2)
{
    auto *temp = obj1;
    
    if( !(obj1 -> greater_than(*obj2)) )
    {
        obj1 = obj2;
        obj2 = temp;
    }
    return;
}


/* Resolve an incoming split. in_split is the incoming struct, our_split
 * is ourselves splitting (only if we need to!) */
template<class KEY, class DATA>
int node<KEY, DATA>::resolve_split(struct split_info<KEY, DATA> *&in_split)
{
    short child_index;
    /* Case 1: We have an incoming data and we're NOT full */
    if(!this->is_full()) {

        //Where will the new child go?
        child_index = (short) data_holder<KEY, DATA>::compare(in_split->push_up_data);

        /* Shift our children to make room for new child */
        for(int i = MAX_DEGREE - 2; i > child_index; --i)
            children[i + 1] = children[i];

        //Connect new child
        this->connect(in_split->new_right, child_index + (short)1);

        //Set new_right to null again
        in_split->new_right = nullptr;

        return this->data_holder<KEY, DATA>::add(in_split->push_up_data);
    }
    /* Case 2: We have incoming data and we ARE full */
    return this->split_internal(in_split);
}

/* Returns the pointer to the next child, depending on the data */
template<class KEY, class DATA>
node<KEY, DATA> *node<KEY, DATA>::next_child(datum<KEY,DATA> const &new_data)
{
    return children[data_holder<KEY, DATA>::compare(new_data)];
}

template<class KEY, class DATA>
node<KEY, DATA> *node<KEY, DATA>::next_child(KEY const &new_data) const
{
    return children[data_holder<KEY, DATA>::compare(new_data)];
}

/* Connect a pointer to a node to our children index */
template<class KEY, class DATA>
void node<KEY, DATA>::connect(node<KEY, DATA> *new_child, short child_index)
{
    this->children[child_index] = new_child;
}

template<class KEY, class DATA>
bool node<KEY, DATA>::is_leaf() const
{
    /* I could use a for loop but this is pretty quick and avoids unnecessary jumps */
    char accum = false;

    //TODO implement a macro here so we don't have to manually change this
    accum += children[0] == NULL;
    accum += children[1] == NULL;
    accum += children[2] == NULL;
    accum += children[3] == NULL;

    return accum == MAX_DEGREE;
}

/* CONSTRUCTOR */
template<class KEY, class DATA>
node<KEY, DATA>::node() : data_holder<KEY, DATA>()
{
    children = new node<KEY, DATA> *[MAX_DEGREE];
    for(int i = 0; i < MAX_DEGREE; ++i)
        children[i] = NULL;
}

/* CONSTRUCTOR WITH ARGUMENTS */
template<class KEY, class DATA>
node<KEY, DATA>::node(datum<KEY,DATA> const &obj) : data_holder<KEY, DATA>(obj)
{
    children = new node<KEY, DATA> *[MAX_DEGREE];
    for(int i = 0; i < MAX_DEGREE; ++i)
        children[i] = NULL;
}

/* COPY CONSTRUCTOR */
template<class KEY, class DATA>
node<KEY, DATA>::node(node<KEY, DATA> const &obj) : data_holder<KEY, DATA>(obj)
{
    children = new node<KEY, DATA> *[MAX_DEGREE];
    short i = 0;
    for(; i < MAX_DEGREE && obj.children[i]; ++i)
        children[i] = new node<KEY,DATA>(*obj.children[i]);
    for(; i < MAX_DEGREE; ++i)
        children[i] = NULL;
}


/* COPY CONSTRUCTOR for the previous class (data_holder)*/
template<class KEY, class DATA>
node<KEY, DATA>::node(data_holder<KEY, DATA> const &obj) : data_holder<KEY, DATA>(obj)
{
    children = new node<KEY, DATA> *[MAX_DEGREE];
    for(int i = 0; i < MAX_DEGREE; ++i)
        children[i] = nullptr;
}

/* DESTRUCTOR */
template<class KEY, class DATA>
node<KEY, DATA>::~node()
{
    delete[] children;
    children = NULL;
}

/* Clears all nodes in this subtree. DOES NOT clear self  */
template<class KEY, class DATA>
void node<KEY, DATA>::clear()
{
    for(int i = 0; i < MAX_DEGREE && children[i]; ++i) {
        children[i]->clear();
        delete children[i];
        children[i] = NULL;
    }
}

