#include <string>
#include <vector>

#ifndef SENTIMENTANALYSIS_VECTORIZE_WINDOW
#define SENTIMENTANALYSIS_VECTORIZE_WINDOW

class node : public std::string
{
public:
    node();
    node(const node& obj);
    explicit node(const std::string &obj);
    ~node();
    node* insert_beginning(const std::string &obj);
    node* insert_end(const std::string &obj);
    node* next();
    node* prev();
    void clear_all();
    const node* find(const std::string &to_find) const;
    node* copy_DLL() const;
protected:
    node* copy_DLL(node *dest) const;
    node *_next;
    node *_prev;
private:
};

class window
{
public:
    window();
    window(const window &obj);
    explicit window(window &&rhs);
    ~window();
protected:
private:
};

#endif //SENTIMENTANALYSIS_VECTORIZE_WINDOW
