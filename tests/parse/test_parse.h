/*
 * 6/25/18 Nicholas Grout
 */
#include <fstream>
#include <iostream>
#include <string>
#include "parse.h"
#include <cxxtest/TestSuite.h>

using namespace std;

/*
 */

class TestParse : public CxxTest::TestSuite
{
    public:
        void testParse(void)
        {
            parse parser;
            parser(example);
            auto size = parser.size();
            TS_ASSERT(size); // Check if 0
            if (!size)
                TS_FAIL("parser did not parse any words!");
            else if (size < 9)
                TS_WARN("parser parsed less than 9 words");
            else
                TS_TRACE("parser finished parsing");
        }
    protected:
    private:
        string example {"This is some example text! Okay? \
            'Here we are,' I can't imagine!"};
};
