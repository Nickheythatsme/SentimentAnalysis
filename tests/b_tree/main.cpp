//
// Created by njgro on 4/27/2018.
//
// #include "b_tree.h"
#include "holder.h"
#include "../testing_classes/case.hpp"
#include "../testing_classes/performance.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;


// Test split and output the results
bool split_test()
{
    std::default_random_engine generator(3);
    std::uniform_int_distribution<int> distribution(1,1000);
    holder<int,int>::B_SIZE = 2 + (distribution(generator) % 4); // B_SIZE between 2, 5

    holder<int,int> a_holder;
    vector<pair<int,int>> values;

    int i;
    for (i=0; i<holder<int,int>::B_SIZE+1; ++i)
    {
        int val = distribution(generator);
        values.emplace_back(make_pair(val, val));
    }
    for (i=0; i <holder<int,int>::B_SIZE; ++i)
        a_holder.push(pair<int,int>(values[i]));

    pair<int,int> &&new_val = pair<int,int>(values[i]);
    auto split_val = a_holder.split(std::move(new_val));
    sort(values.begin(), values.end());

    return split_val.middle_data == values[holder<int,int>::B_SIZE/2];
}

bool performance_split(size_t n)
{
    holder<int,int>::B_SIZE = n - 1;
    holder<int,int> holder1;
    for (size_t i=0; i<n; ++i)
    {
        holder1.push(std::make_pair(i,i));
    }
    holder1.split(std::make_pair(n,n));
    return true;
}

int main(int argc, char *argv[])
{
    test_case case1("Split test", split_test);
    case1.set_iterations(10000);
    case1.start();
    cout << case1.get_result() << endl;
    if (!case1.get_result().passed)
        return 2;
    
    performance_test perf1("Performance split test", performance_split, 1000, 200);
    perf1.start();
    cout << perf1.get_result() << endl;
}
