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
        void testLength(void)
        {
			auto parser = runParser();
			auto size = parser.size();
            TS_ASSERT(size); // Check if 0
            if (!size)
                TS_FAIL("parser did not parse any words!");
            else if (size < 9)
                TS_WARN("parser parsed less than 9 words");
            else
                TS_TRACE("parser finished parsing: ");
			for (const auto & w : parser)
				TS_TRACE(w);
        }
		void testDelims()
		{
			TS_TRACE("Testing the presence of a delimiter");
			auto parser = runParser();
			for (const auto & word : parser)
				for (const auto & w_char : word)
					for (const auto & d_char : delims)
						if (d_char == w_char)
							TS_FAIL("Delim character failed: " + d_char + word);
			TS_TRACE("No delimeters found in word");
		}
    protected:
    private:
		parse runParser()
		{
			parse parser { delims.c_str() };
            parser(example);
			return parser;
		}
        string example{ "This is some example text! Okay? \
            'Here we are,' I can't imagine!" };
		string delims{ "'\",.()! " };
};
