//
// Created by njgro on 4/27/2018.
//
// #include "b_tree.h"
#include "holder.h"
#include <iostream>
#include <string>
using namespace std;

void test_atom(atomic_int &c)
{
    auto temp = c.load();
    temp++;
    c = temp;
}

int main(int argc, char *argv[])
{
    atomic_int c;
    c.store(0);
    for (int i = 0; i < 10; ++i)
    {
        thread t(test_atom, std::ref(c));
        t.detach();
    }
    cout << c << endl;
}

