#include "test_parse.h"

bool test_parse(const char *path)
{
    text_package p(path);
    return parse_text(p);
}

bool parse_text(text_package &p)
{
    parse parser;

    // Start timing the program
    auto start = std::chrono::system_clock::now();
    for(auto c_ptr : p)
    {
        parser(c_ptr);
    }
    auto end = std::chrono::system_clock::now();

    // Output the result
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed time: " << elapsed_seconds.count() << endl
         << "Size: " << endl
         << "\tbytes: " << p.bytes() << endl
         << "\twords: " << parser.size() << endl
         << "\tfiles: " << p.size() << endl;

    return test_object<parse>(parser);
}
