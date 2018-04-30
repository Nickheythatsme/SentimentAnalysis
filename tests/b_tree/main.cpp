//
// Created by njgro on 4/27/2018.
//
// #include "b_tree.h"
#include "holder.h"
#include <iostream>
#include <string>
#include <thread>
#include <zconf.h>
using namespace std;

void test_mutex(int &c, mutex &int_lock)
{
    lock_guard<mutex> guard(int_lock);
    for (int i=0; i < 10; ++i)
    {
        ++c;
        usleep(rand() % 10);
    }
}

void test_atomic(atomic_int &c)
{
    for (int i=0; i < 10; ++i)
    {
        ++c;
        usleep(rand() % 10);
    }

}

void test_reg(int &c)
{
    for (int i=0; i < 10; ++i)
    {
        ++c;
        usleep(rand() % 10);
    }
}

int main(int argc, char *argv[])
{
    auto T_SIZE = 10;
    thread threads[T_SIZE];

    // Mutex testing
    {
        int mutex_int = 0;
        mutex int_lock;
        for (int i = 0; i < T_SIZE; ++i) {
            threads[i] = thread(test_mutex, std::ref(mutex_int), std::ref(int_lock));
        }
        for (int i = 0; i < T_SIZE; ++i)
            threads[i].join();
        cout << "Mutex int: " << mutex_int << endl;
        cout << "Mutex size: " << sizeof(mutex_int) << endl;
        cout << endl;
    }

    {
        atomic_int atom_int;
        atom_int = 0;
        // Atomic testing
        for (int i = 0; i < T_SIZE; ++i)
        {
            threads[i] = thread(test_atomic, std::ref(atom_int));
        }
        for (int i = 0; i < T_SIZE; ++i)
            threads[i].join();
        cout << "Atomic int: " << atom_int << endl;
        cout << "Atomic size: " << sizeof(atom_int) << endl;
        cout << endl;
    }

    {
        // Regular int testing
        int reg_int = 0;
        for (int i = 0; i < T_SIZE; ++i)
        {
            threads[i] = thread(test_reg, std::ref(reg_int));
        }
        for (int i = 0; i < T_SIZE; ++i)
            threads[i].join();
        cout << "regular: " << reg_int << endl;
        cout << "regular size: " << sizeof(reg_int) << endl;
        cout << endl;
    }
}

