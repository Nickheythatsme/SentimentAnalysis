/*
6/26/2018 Nicholas Grout
*/

#include "btree.hpp"
#include <cxxtest/TestSuite.h>

using std::string;

class TestHolder : public CxxTest::TestSuite
{
public:
	void testPush(void)
	{
		holder<int, string> h;
		TS_ASSERT(h.full());
	}
	void testSplit(void)
	{
		holder<int, string> h;
		for (size_t i = 0; i < BSIZE; ++i)
		{
			h.push(std::make_pair(i,"test"));
		}
		auto split_result = h.split(std::make_pair(BSIZE,"test"));

        // TEST new rhs data by comparing i to the holder
        for (size_t i=(BSIZE/2)+1, j=0; i<=BSIZE; ++i, ++j)
        {
            auto result = split_result.new_rhs->compare(i);
            TS_ASSERT(result == j);
        }

        // TEST push up data
        TS_ASSERT(BSIZE/2 == split_result.push_up->first);

        // TEST lhs (the original old holder)
        for (size_t i=0; i<=BSIZE/2; ++i)
        {
            auto result = h.compare(i);
            TS_ASSERT(result == i);
        }
	}
protected:
private:

};
