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
		void testReplaceAll()
		{
            char example[] = "this is my this is my this is my example!!!YO!";
            auto result = replace_all(example, "this", 'a');
            TS_ASSERT(result == 3);
		}
        void testRemoveAll()
        {
            char* result = remove_all(example.c_str(), "some");
            string message {"remove_all result: "};
            message += result;

            TS_TRACE(message.c_str());
            TS_ASSERT(strcmp(result, "This is  example text!  Okay? 'Here we are,' I can't imagine!") == 0);
            delete [] result;
        }
        void testRemoveAllTimed()
        {
            string filename {"../tests/text_samples/big.txt"};
            ifstream fin(filename);
            string contents;
            char delim[] = "a";

            if (!fin)
            {
                TS_TRACE("unable to find file: " + filename);
                return;
            }

            while( fin.good() && contents.size() < 1000000)
            {
                contents += fin.get();
            }

            TS_TRACE("Read " + std::to_string(contents.size()) + " bytes");

            // Start timing
            auto start = std::chrono::high_resolution_clock::now();
            auto result = remove_all(contents.c_str(), delim);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::micro> elapsed = end - start;
            TS_TRACE("test completed in " + std::to_string(elapsed.count()) + " us");
        }
    protected:
    private:
        string example{ "This is some example text! some Okay? 'Here we are,' I can't imagine!" };
};
