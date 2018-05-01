//
// Created by njgro on 4/27/2018.
//
// #include "b_tree.h"
#include "holder.h"
#include "../test_case.h"
#include <iostream>
#include <string>
#include <thread>
using namespace std;

const int T_SIZE = 10;

/* Testing thread safety */
/*
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
    for (auto &a_thread : threads)
        a_thread = thread(thread_safe_func, std::ref(a_holder));
    for (auto &a_thread : threads)
        a_thread.join();
    return true;
}
*/

// Test split and output the results
/*
bool split_test(holder<int,int> &a_holder, nullptr_t &n)
{
    for (int i=0; i < 10; ++i)
    {
        auto p = std::pair<int, int>(i,i);
        if (a_holder.full())
        {
            auto s = a_holder.split(make_pair(i,i));

        }
        else
            a_holder.push(std::make_pair(i,i));
    }
    return true;
}
*/

int main(int argc, char *argv[])
{
    /*
    unit_test<holder<int>,nullptr_t> thread_safety(thread_safe, nullptr);
    thread_safety.set_name("Thread safety");
    thread_safety.start();
    cout << thread_safety.get_result() << endl;
    */

    /*
    unit_test<holder<int,int>, nullptr_t> split_testing(split_test, nullptr);
    split_testing.set_name("split test");
    cout << split_testing.start() << endl;
    */
    holder<int,int> hold;
    hold.push(std::make_pair(1,1));
}
