//
// Created by njgro on 4/27/2018.
//
// #include "b_tree.h"
#include "holder.h"
#include "../test_case.h"
#include <iostream>
#include <string>
#include <thread>
#include <zconf.h>
using namespace std;

const int T_SIZE = 10;


bool thread_safe_func(holder<int> &a_holder)
{
    for(int i=0; i < 10; ++i)
    {
        if(a_holder.full())
            a_holder.clear();
        a_holder.push(rand() % 100);
    }
}

bool thread_safe(holder<int> &a_holder, nullptr_t &n)
{
    thread threads[T_SIZE];
    for (int i=0; i < T_SIZE; ++i)
        threads[i] = thread(thread_safe_func, std::ref(a_holder));
    for (int i=0; i < T_SIZE; ++i)
        threads[i].join();
    return true;
}

int main(int argc, char *argv[])
{
    unit_test<holder<int>,nullptr_t> t(thread_safe, nullptr);
    t.start();
    cout << t.get_result() << endl;
}

