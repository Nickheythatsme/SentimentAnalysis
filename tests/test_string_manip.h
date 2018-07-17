/*
 * 6/25/18 Nicholas Grout
 */
#include <iostream>
#include <string>
#include <cxxtest/TestSuite.h>
extern "C" {
    #include "string_manip.h"
}

using namespace std;

class TestStringManip : public CxxTest::TestSuite
{
    public:
        void testFind(void)
        {
            auto result = find(example.c_str(), "some", strlen("some"));
            TS_ASSERT(result == 8);
        }
		void testReplaceAll()
		{
            char example[] = "this is my this is my this is my example!!!YO!";
            auto result = replace_all(example, "this", 'a');
            TS_ASSERT(result == 3);
		}
    protected:
    private:
        string example{ "This is some example text! Okay? \
            'Here we are,' I can't imagine!" };
};
