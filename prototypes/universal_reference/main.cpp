#include "class.h"

/*
 * Compilers automatically change ownership of little a's data.
 * the local object 'a' will NOT be destroyed at the end of this 
 * returntion, and will also not have its move constructor called
 * it will just be moved into the return value and ownership will
 * be transferred to whereever the object is returning
 */
A return_good(const char *word)
{
    A a(word);
    return a;
}

/*
 * This interfeers with the compiler's optimization and makes the
 * local object 'a' have its data moved to the return value,
 * then its destructor is called.
 */
A return_bad(const char *word)
{
    A a(word);
    return std::move(a);
}

template<typename T>
void universal_reference(T &&a)
{
    a.setText("this!");
    return;
}

template<typename T>
void rvalue_reference(const T &&obj)
{
    T t(obj);
    return;
}

int main(int argc, char **argv)
{
    /* How to return an object */
    cout << "Returning an object: " << endl;
    {
        A a {return_good("one!")};
        cout << a << endl;
    }
    cout << endl << endl;


    /* How to make a universal reference to an object */
    cout << "Universal reference" << endl;
    {
        auto&& a = A(); //universal reference
        cout << a << endl;
        universal_reference(a);
        cout << a << endl;
    }
    cout << endl << endl;

    /* rvalue vs lvalue */
    cout << "rvalue vs lvalue" << endl;
    {
        A &&a = A();

        // lvalue
        universal_reference(a);

        // rvalue
        universal_reference(std::move(a));
        rvalue_reference(std::move(a));
    }
    cout << endl << endl;

}
