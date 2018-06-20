#include <fstream>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "text_package.h"
#include "parse.h"

using namespace std;

/*
 * Test preconfigured text
 */
BOOST_AUTO_TEST_CASE(simple_test) 
{
    string sample_text {"Shouldn't be too bad. Hardest part would be just staying in place. Looks like they all have tanks of air except for Radcliffe and the girl in front. "};
	string delims{ ".,'\\()" };
    parse parser;

    // Start parsing
    parser(sample_text);

	BOOST_CHECK_MESSAGE(parser.size() == 24, "parser result: " << parser.size());
	for (const auto &c : parser)
	{
		for (const auto &d : delims)
		{
			if (c.find(d) != string::npos)
				BOOST_ERROR("Found " << d << " in string " << c);
		}
	}
}

int main(int argc, char *argv[])
{
	/*
    if (argc < 2)
    {
        cout << "Unable to perform long test (no pattern given)" << endl;
        exit(EXIT_FAILURE);
    }

	text_package package;
    try {
        for (size_t i=1; i<argc; ++i)
        {
            package.load_files(argv[i]);
        }
		cout << "Finished reading " << package.size() << " files ("
			<< package.bytes() / 1000 << " kilobytes)" << endl;
    } catch(const text_package_error &err) {
        cerr << err << endl;
        exit(EXIT_FAILURE);
    }
	*/
	system("pause");

    return 0;
}

