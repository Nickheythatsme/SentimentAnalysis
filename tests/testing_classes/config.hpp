#ifndef SENTIMENTANALYSIS_TEST_GENERAL_H
#define SENTIMENTANALYSIS_TEST_GENERAL_H

#include <iostream>
#include <fstream>
#include <exception>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINPAUSE system("pause");
#else
#define WINPAUSE
#endif

using std::string;
using std::endl;

// Defining a pointer to a function so the user may add their own test functions
template<class T, class D>
using custom_function = bool (*)(T &, D &);

class test_err : public std::exception
{
public:
    test_err(const string &_message, const string &_name) {message = _message; name = _name;}
    string message;
    string name;
    friend std::ostream& operator<<(std::ostream &out, const test_err &rhs);
};

/* test_err implementation */
std::ostream& operator<<(std::ostream &out, const test_err &rhs)
{
    out << "Test Error: " << endl
        << "Name: " << rhs.name << endl
        << "Message: " << rhs.message << endl;
    return out;
}

// Enable logging of test results (re-route cout, cerr)
// Give this class a test name and it_will_fileize_it.log
class logging
{
    public:
        logging() = delete;
        logging(const logging &rhs) = delete;
        logging(logging &&rhs) = delete;
        explicit logging(const string &test_name, bool verbose=false);
        ~logging();
    private:
        string file_name {}; // defaults to {name}.log
        void set_cout();
        void revert_cout();
        std::streambuf *default_cout {nullptr}; // default cout buffer
        std::ofstream out_file;
};


// Configuration for a test, as well as the data and object if provided
class config
{
public:
    config(string _name);
    config() = default;
    config(const config &obj) = default;
    config(config &&obj) = default;
    ~config() = default;
    // Setters
    config& set_verbose(bool value=true) {
        verbose = value; 
        return *this;}
    config& set_iterations(size_t _iterations) {
        iterations = _iterations; 
        return *this;}
    config& set_name(string _name) {
        name = _name;
        return *this;}
    // Getters
    auto get_name() const {return name;}
    auto get_iterations() const {return iterations;}
    auto get_verbose() const {return verbose;}
protected:
    string name {"test"};
    bool verbose {true};
    size_t iterations {1};
private:
};

config::config(string _name) :
    name(std::move(_name))
{ }

/* config implementation */
// Enable logging of test results (re-route cout, cerr)
logging::logging(const string &_file_name, bool verbose)
{
    if (verbose) return;
    auto file_name(_file_name);
    for (auto &c : file_name)
        if (' ' == c)
            c = '_';
    file_name = file_name + ".log";
    out_file.open(file_name.c_str());
        default_cout = std::cout.rdbuf(out_file.rdbuf());
}

logging::~logging()
{
    // revert cout
    if (default_cout)
    {
        std::cout.rdbuf(default_cout);
        default_cout = nullptr;
    }

    // close out_file
    if (out_file.is_open())
        out_file.close();
}

#endif // SENTIMENTANALYSIS_TEST_GENERAL_H
