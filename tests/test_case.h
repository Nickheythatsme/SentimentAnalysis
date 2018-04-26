#include <chrono>
#include <iostream>

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

struct test_err
{
    test_err(const string &_message, const string &_name) {message = _message; name = _name;}
    string message;
    string name;
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

    bool passed {false};
    string name {};
    size_t iterations {0};
    std::chrono::duration<double> average {0};
    std::chrono::duration<double> total {0};
};

struct configuration
{
    string name {};
    bool verbose {true};
    bool run_basic {true};
    bool run_big_o {true};
    bool run_iteration {true};
    size_t iterations {1};
};

// Configuration of a test case
template<class T, class D>
class unit_test
{
    public:
        unit_test() = delete;
        unit_test(custom_function<T,D> _func, const D &_data);
        unit_test(custom_function<T,D> _func, const D &_data, const T &obj);
        unit_test(custom_function<T,D> _func, const D &_data, const configuration &config);
        unit_test(custom_function<T,D> _func, const D &_data, const T &obj, const configuration &config);
        unit_test(const unit_test<T,D> &rhs) = default;
        unit_test(unit_test<T,D> &&rhs) = default;
        ~unit_test() = default;
        test_result start();

        // Test unit_test
        void set_config(const configuration & _config) {config = _config;}
        void set_data(const D &_data) {data = _data;}
        void set_obj(const T &_obj) {obj = _obj;}
        void set_name(const T &_name) {name = _name;}
        void set_func(const T &_func) {func = _func;}

        // Get test values
        configuration& get_config() {return config;}
        auto get_obj()    { return obj; }
        auto get_data()   { return data; }
        auto get_name()   { return name; }
        auto get_result() { return result; }
    protected:
    private:
        decltype(auto) commence_test();
        T obj;
        D data {};
        string name {};
        custom_function<T,D> func;
        test_result result;
        configuration config;
};

#include "test_case.cpp"
#endif //SENTIMENTANALYSIS_TEST_CASE_H 

