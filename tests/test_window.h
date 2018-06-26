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
		auto s_ptr = std::make_shared<string>("test string!");
		w.add(std::shared_ptr<string>(s_ptr));
		size_t result = w.find("test string!");
		TS_ASSERT(result != string::npos);
	}
protected:
private:

};