/*
 * 6/25/18 Nicholas Grout
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cxxtest/TestSuite.h>
#include <chrono>
extern "C" {
    #include "string_manip.h"
}

using namespace std;

class TestStringManip : public CxxTest::TestSuite
{
    public:
        void testFind(void)
        {
            auto count = 0;
            auto current = example.c_str();
            auto result = find(current, "some", strlen("some"));
            while (result != S_FAIL)
            {
                ++count;
                current += sizeof(char) * (result + 1);
                result = find(current, "some", strlen("some"));
            }
            TS_TRACE("count: " + std::to_string(count));
            TS_ASSERT(count == 2);
        }
        void testRemove()
        {
            char* result = remove(example.c_str(), "some");
            string message {"remove result: "};
            message += result;

            TS_TRACE(message.c_str());
            TS_ASSERT(strcmp(result, "This is  example text!  Okay? 'Here we are,' I can't imagine!") == 0);
            delete [] result;
        }
    protected:
    private:
        string example{ "This is some example text! some Okay? 'Here we are,' I can't imagine!" };
};
