
#include "window.h"
window::window()
{

}
window::window(const window &obj)
{

}
window::window(window &&rhs)
{

}
window::~window()
{

}

/*
 * NODE FUNCTIONS
 */
// CONSTRUCTOR
node::node()
{
    _next = _prev = nullptr;
}
// CONSTRUCTOR WITH ARGUMENTS
node::node(const std::string &obj)
    : basic_string(obj)
{
    _next = _prev = nullptr;
}
// COPY CONSTRUCTOR
// does NOT copy the whole DLL
node::node(const node& obj)
    : basic_string(obj)
{
    _next = _prev = nullptr;
}
//DESTRUCTOR
node::~node()
{
    _next = _prev = nullptr;
}
/*
 * Insert a new word at the beginning of the list.
 * Returns the new head of the list
 */
node* node::insert_beginning(const std::string &obj)
{
    if(!_prev){
        _prev = new node(obj);
        _prev->_next = this;
        return _prev;
    }
    return _prev->insert_beginning(obj);
}
/*
 * Insert a new word at the end of the list.
 * Returns the new end of the list
 */
node* node::insert_end(const std::string &obj)
{
    if (!_next){
        _next = new node(obj);
        _next->_prev = this;
        return _next;
    }
    return _next->insert_end(obj);
}
node *node::next()
{
    return _next;
}
node *node::prev()
{
    return _prev;
}
/*
 * Clears all nodes after this node, sets _next and _prev to nullptr
 */
void node::clear_all()
{
    if (!_next)
        return;
    _next->clear_all();
    delete _next;
    _prev = _next = nullptr;
}

/*
 * Searches all words AFTER this word, does not search previous words
 */
const node* node::find(const std::string &to_find) const
{
    if (!_next)
        return nullptr;
    if (this->std::string::compare(to_find) == 0)
        return this;
    return _next->find(to_find);
}

node* node::copy_DLL() const
{
    auto *head = new node(*this);
    return copy_DLL(head);
}

/*
 * Recursively copies all nodes AFTER this node
 * returns a pointer to the
 */
node* node::copy_DLL(node *dest) const
{
    if (_next) {
        dest->_next = new node(*_next);
        dest->_next->_prev = dest;
        _next->copy_DLL(dest->_next);
        return dest;
    }
    return dest;
}

