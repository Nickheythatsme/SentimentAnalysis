#include "window.h"

// CONSTRUCTOR
window::window()
{
    head = tail = nullptr;
    _size = 0;
}

// CONSTRUCTOR with arguments
window::window(const string *words, size_t len)
{
    head = tail = nullptr;

    for (auto i = 0; i < len; ++i)
        add_word(words[i]);
}

// COPY CONSTRUCTOR
window::window(const window &obj)
{
    // Copy the DLL from obj
    _size = copy_DLL(obj.head, head, tail);
}

// DESTRUCTOR
window::~window()
{
    remove_all(head);
    delete head;
    head = nullptr;
}

// Copy all of the words in the DLL, recursively
size_t window::copy_DLL(const word *obj_head, word *&self_head, word *&self_tail)
{
    if (!obj_head) {
        self_head = nullptr;
        return 0;
    }

    // Make a new node
    self_head = new word(*obj_head);

    // Set the previous ptr to the tail (which is the last node copied)
    self_head->prev = self_tail;

    // Move tail up to the new node
    self_tail->next = self_head;

    // Make the recursive call. 
    return copy_DLL(obj_head->next, self_head->next, self_tail->next) + 1;
}

// Assignment operator
window &window::operator=(const window &src)
{
    remove_all(head);
    _size = copy_DLL(src.head, head, tail);
}

// Add words from another window to this window
window &window::operator+=(const window &to_add)
{
    word *temp_head, *temp_tail;

    // Copy the DLL from to_add to a new DLL
    _size += copy_DLL(to_add.head, temp_head, temp_tail);

    // Attach the new DLL to our DLL
    this->tail->next = temp_head;
    // Attach the prev ptr from temp_head to our DLL
    temp_head->prev = this->tail;
    // Move our tail to temp_tail
    this->tail = temp_tail;

    return *this;
}

// Add a word to this window (at the end)
window &window::operator+=(const string &to_add)
{
    this->add_word(to_add);
    return *this;
}

// Output all words to the ostream through the extraction operator
std::ostream &operator<<(std::ostream &out, const window &obj)
{
    // TODO remove when not debugging
    obj.display(out, obj.head);
    out << std::endl;
    return obj.display_reverse(out, obj.tail);
}

// Output all words to the ostream object in order
std::ostream &window::display(std::ostream &out, const word *head) const
{
    if (!head) return out;
    out << *head;
    if (head->next)
        out << ", ";
    return display(out, head->next);
}

// TODO remove when not debugging
std::ostream &window::display_reverse(std::ostream &out, const word *head) const
{
    if (!head) return out;
    out << *head;
    if (head->prev)
        out << ", ";
    return display_reverse(out, head->prev);
}

// Returns the number of words in the window
size_t window::size() const
{
    return _size;
}

// Add a word onto the end of the DLL. ALSO increments _size by 1
void window::add_word(const string &to_add)
{
    auto *new_node = new word(to_add);
    _size += 1;

    // CASE no words in the DLL yet
    if (!head) {
        head = new_node;
        tail = new_node;
    }

        // CASE words already in the DLL
    else {
        tail->next = new_node;

        // Set the previous ptr
        new_node->prev = tail;

        // Move tail to the new node
        tail = tail->next;
    }
}

// Remove all the nodes in the DLL
void window::remove_all(word *head)
{
    if (!head) return;
    remove_all(head->next);
    delete head->next;
}
