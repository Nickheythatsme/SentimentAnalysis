#include <chrono>
#include <iostream>
#include <fstream>

#ifndef SENTIMENTANALYSIS_TEST_CASE_H
#define SENTIMENTANALYSIS_TEST_CASE_H

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

class test_err
{
public:
    test_err(const string &_message, const string &_name) {message = _message; name = _name;}
    string message;
    string name;
    friend std::ostream& operator<<(std::ostream &out, const test_err &rhs);
};

// Result of a test. Also formats the display
struct test_result
{
    test_result() = default;
    test_result(const test_result &rhs) = default;
    test_result(test_result &&rhs) = default;
    ~test_result() = default;
    friend std::ostream& operator<<(std::ostream& out, const test_result &rhs);
    static string display_time(const std::chrono::duration<double> &t);
    test_result&operator=(const test_result &_test_result) = default;

    bool passed {false};
    string name {};
    size_t iterations {0};
    std::chrono::duration<double> average {0};
    std::chrono::duration<double> total {0};
};

// Configuration for a test, as well as the data and object if provided
template<class T, class D>
class configuration
{
public:
    configuration() = delete;
    explicit configuration(custom_function<T,D> _func, const D &_data);
    explicit configuration(custom_function<T,D> _func, const D &_data, const T &_obj);
    configuration(const configuration &obj) = default;
    configuration(configuration &&obj) = default;
    ~configuration() = default;
    // Setters
    configuration<T,D>& set_verbose(bool value=true) 
    {
        verbose = value; 
        return *this;
    }
    configuration<T,D>& set_iterations(size_t _iterations) 
    {
        iterations = _iterations; 
        return *this;
    }
    configuration<T,D>& set_name(string _name) 
    {
        name = _name;
        return *this;
    }
    configuration<T,D>& set_object(const T &_obj) 
    {
        obj = _obj;
        return *this;
    }
    configuration<T,D>& set_data(const D &_data) 
    {
        data = _data;
        return *this;
    }
    configuration<T,D>& set_copy_data(bool _copy_data) 
    {
        copy_data=_copy_data;
        return *this;
    }
    // Getters
    auto get_name() const {return name;}
    auto get_iterations() const {return iterations;}
    auto get_verbose() const {return verbose;}
    auto get_object() const {return obj;}
    auto get_data() const {return data;}
protected:
    string name {"test"};
    bool verbose {true};
    size_t iterations {1};
    D data {};
    T obj;
    custom_function<T,D> func;
    bool copy_data {true};
private:
};

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

// Configuration of a test case
template<class T, class D>
class unit_test : public configuration<T,D>
{
    public:
        unit_test() = delete;
        unit_test(custom_function<T,D> _func, const D &_data);
        unit_test(custom_function<T,D> _func, const D &_data, const T &obj);
        unit_test(const unit_test<T,D> &rhs) = default;
        unit_test(unit_test<T,D> &&rhs) = default;
        ~unit_test() = default;
        test_result start();

        // Return the result of the test
        const test_result& get_result() { return result; }
    protected:
        decltype(auto) commence_test(T &obj, D &data);
    private:
        test_result result;
};

#include "test_case.cpp"
#endif //SENTIMENTANALYSIS_TEST_CASE_H 

