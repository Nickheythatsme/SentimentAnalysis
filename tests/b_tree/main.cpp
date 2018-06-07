//
// Created by njgro on 4/27/2018.
//
// #include "b_tree.h"
#include "holder.h"
#include "../test_case.h"
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

const int B_SIZE = 3;

// Test split and output the results
bool split_test(nullptr_t &v, nullptr_t &n)
{
    std::default_random_engine generator(3);
    std::uniform_int_distribution<int> distribution(1,10);

    holder<int,int> a_holder;
    vector<pair<int,int>> values;

    int i;
    for (i=0; i<B_SIZE+1; ++i)
    {
        int val = distribution(generator);
        values.emplace_back(make_pair(val, val));
    }
    for (i=0; i <B_SIZE; ++i)
        a_holder.push(pair<int,int>(values[i]));

    pair<int,int> &&new_val = pair<int,int>(values[i]);
    auto split_val = a_holder.split(std::move(new_val));
    sort(values.begin(), values.end());

    return split_val.middle_data == values[B_SIZE/2];
}

int main(int argc, char *argv[])
{
    unit_test<nullptr_t, nullptr_t> split_testing(split_test, nullptr);
    split_testing.set_name("split test")
        .set_verbose(false)
        .set_iterations(1000);
    split_testing.start();
    auto result =  split_testing.get_result();
    cout << result << endl;

    

    return  result.passed;
}
