#include <fstream>
#include <iostream>
#include <string>
#include "../testing_classes/case.hpp"
#include "../testing_classes/performance.hpp"
#include "../testing_classes/timer.hpp"
#include "text_package.h"
#include "parse.h"

using std::cout;
using std::endl;

const char *filename;
text_package package;

bool test_long()
{
    parse parser;
    for (auto const &text : package)
    {
        parser(text);
    }
    return true;
}

bool test_performance(size_t n)
{
    parse parser;
    n = (n > parser.size()) ? parser.size() : n;
    for (size_t i=0; i<n; ++i)
    {
        parser(package[i]);
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Unable to perform long test (no pattern given)" << endl;
        exit(EXIT_FAILURE);
    }

    try {
        test_timer read_time;
        read_time.start();
        for (size_t i=1; i<argc; ++i)
        {
            package.load_files(argv[i]);
            cout << "Reading directory: " << argv[i] << endl;
        }
        read_time.end();
        cout << "Finished reading " << package.size() << " files (" 
             << package.bytes()/1000 << " kilobytes)" << endl
             << "Time: " << read_time << endl;
    } catch(const text_package_error &err) {
        cerr << err << endl;
        return 2;
    }

    test_case case1("long parse test", test_long);
    case1.set_iterations(1);
    case1.set_verbose(true);
    case1.start();
    cout << case1.get_result() << endl;

    performance_test perf1 ("Performance parse test", test_performance, 1000, 10000);
    perf1.start();
    cout << perf1.get_result() << endl;

    return 0;
}
