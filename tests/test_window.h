/*
6/26/2018 Nicholas Grout
*/

#include "window.h"
#include <cxxtest/TestSuite.h>

using std::string;

class TestWindow : public CxxTest::TestSuite
{
public:
	void testAdd(void)
	{
		window w;
		string test_str{ "test string!" };
		auto s_ptr = std::make_shared<window>(test_str);
		w.add(std::shared_ptr<window>(s_ptr));
		size_t result = w.find_word(test_str);
		TS_ASSERT(result != string::npos);
	}
protected:
private:

};