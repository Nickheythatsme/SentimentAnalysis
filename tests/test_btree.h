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
		h.split(std::make_pair(100,"test"));
		// TODO finish split, add asserts!
	}
protected:
private:

};