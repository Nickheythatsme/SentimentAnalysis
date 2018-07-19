/*
 * 6/25/18 Nicholas Grout
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cxxtest/TestSuite.h>
#include "parse.h"

using namespace std;

class TestStringManip : public CxxTest::TestSuite
{
    public:
        void testParse()
        {
            TS_TRACE("Starting simple parse test");
            std::vector<string> delims {"his","is",","};

            parse parser {delims};
            auto result = parser(example);
            for (const auto & d : delims)
            {
                for (const auto & word : result)
                {
                    if (word.find(d) != std::string::npos)
                    {
                        TS_ASSERT("delimiter found in result");
                    }
                }
            }
        }
    protected:
    private:
        string example{ "This is some example text! some Okay? 'Here we are,' I can't imagine!" };
};
