/*
6/26/2018 Nicholas Grout
*/

#define DEBUG
#include "btree.hpp"
#include <cxxtest/TestSuite.h>
#include <random>
#include <chrono>
using std::string;

class TestBtree : public CxxTest::TestSuite
{
public:
    void testNodeInsert(void)
    {
        node<int, int> n;
    }

    void testNodePush(void)
    {
        auto new_node = new node<int, int>();
        auto new_root = new_node->insert(std::make_pair(0,0));
        TS_ASSERT(new_node->is_leaf());
    }
    void testNodeSplit(void)
    {
        auto new_node = new node<int, int>();
    }
protected:
private:
    std::random_device r;
    std::default_random_engine r_engine { r() };
};
