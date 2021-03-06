/*
6/26/2018 Nicholas Grout
*/

#define DEBUG
#include "btree.hpp"
#include <cxxtest/TestSuite.h>
#include <random>
#include <chrono>
using std::string;

class TestHolder : public CxxTest::TestSuite
{
public:
	void testPush(void)
	{
		holder<int, string> h;
		TS_ASSERT(h.is_full());
	}
	void testSplit(void)
	{
		holder<int, string> h;
        split_holder<int,string> split_result;

		for (size_t i = 0; i < BSIZE; ++i)
		{
			h.push(std::make_pair(i,"test"));
		}
		h.split(std::make_pair(BSIZE,"test"), split_result);

        // TEST new rhs data by comparing i to the holder
        for (size_t i=(BSIZE/2)+1, j=0; i<=BSIZE; ++i, ++j)
        {
            auto result = split_result.new_rhs->first_greater(i);
            TS_ASSERT(result == j);
        }

        // TEST push up data
        TS_ASSERT(BSIZE/2 == split_result.push_up->first);

        // TEST lhs (the original old holder)
        for (size_t i=0; i<=BSIZE/2; ++i)
        {
            size_t result = h.first_greater(i);
            TS_ASSERT(result == i);
        }
	}

    void testSort(void)
    {
        TS_TRACE("testing sorting");

        for (size_t t=0; t<1000000; ++t)
        {
            std::uniform_int_distribution<int> uniform_dist(0, 100);
            holder<int, string> h;

            for (size_t i=0; i<BSIZE; ++i)
            {
                h.push( std::make_pair(uniform_dist(r_engine), "test") );
            }
            TS_ASSERT(h.is_sorted(h.data.get(), h.data_count));
        }
    }

    void testCustomSort(void)
    {
        holder<string, string>::compare = [] (const string &lhs, const string &rhs)
        {
            return lhs[0] < rhs[0];
        };
        holder<string, string> h;
        h.push(std::make_pair("a","a"));
        h.push(std::make_pair("d","d"));
        h.push(std::make_pair("c","c"));
        h.push(std::make_pair("b","b"));

        for (size_t i=0; i<4; ++i)
        {
            TS_TRACE(h.data[i].first);
        }

    }

    void testNodeInsert(void)
    {
        node<int, int> n;
    }

    void testNodePush(void)
    {
        auto *new_node = new node<int, int>();
        auto new_root = new_node->insert(std::make_pair(0,0));
        TS_ASSERT(new_node->is_leaf());
    }
protected:
private:
    std::random_device r;
    std::default_random_engine r_engine { r() };
};
