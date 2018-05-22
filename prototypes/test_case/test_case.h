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
// T == object
// D == data
// bool custom_function(T &obj, D &data)
template<class T, class D>
using custom_function = bool (*)(T &, D &);

class test_err
{
public:
    test_err(const string &_message) {message = _message;}
    test_err(const string &_message, const string &_name) {message = _message; name = _name;}
    string message;
    string name {"Unknown"};
    friend std::ostream& operator<<(std::ostream &out, const test_err &rhs);
};

// Result of a test. Also formats the display
struct test_result
{
    test_result() = default;
    test_result(const string &_name) : name(_name) {}
    test_result(const test_result &rhs) = default;
    test_result(test_result &&rhs) = default;
    ~test_result() = default;
    friend std::ostream& operator<<(std::ostream& out, const test_result &rhs);
    static string display_time(const std::chrono::duration<double> &t);
    test_result&operator=(const test_result &_test_result) = default;

    bool started {false};
    bool passed {false};
    string name {};
    size_t iterations {0};
    std::chrono::duration<double> average {0};
    std::chrono::duration<double> total {0};
};

class base_config
{
public:
    base_config() = default;
    base_config(const string &_name, bool _verbose, bool _copy_data, size_t _iterations);
    base_config(const base_config &rhs) = default;
    base_config(base_config &&rhs) = default;
    ~base_config() = default;
    // Setters 
    void set_verbose(bool value=true) {verbose = value;}
    void set_iterations(size_t _iterations) {iterations = _iterations;}
    void set_name(const string &_name) {name = _name;}
    void set_copy_data(bool _copy_data) {copy_data=_copy_data;}

    // Getters
    auto get_name() const {return name;}
    auto get_iterations() const {return iterations;}
    auto get_verbose() const {return verbose;}
    auto get_copy_data() const {return copy_data;}

    // Assignment operator
    base_config& operator=(const base_config &rhs);
protected:
    string name;
    bool verbose {true};
    bool copy_data {true};
    size_t iterations {1};
private:
};

// Configuration for a test, as well as the data and object if provided
template<class T, class D>
class configuration : public base_config
{
public:
    configuration() = delete;
    explicit configuration(custom_function<T,D> _func, const T &_obj, const D &_data);
    explicit configuration(custom_function<T,D> _func, T &&_obj, D &&_data);
    configuration(const configuration &obj) = default;
    configuration(configuration &&obj) = default;
    ~configuration() = default;

    // Setters
    configuration& set_object(const T &_obj) {obj = _obj; return *this;}
    configuration& set_data(const D &_data) {data = _data; return *this;}
    configuration& set_base_config(const base_config &rhs) {base_config::operator=(rhs); return *this;}

    // Getters
    const T& get_object() const {return obj;}
    const D& get_data() const {return data;}
protected:
    custom_function<T,D> func;
    D data;
    T obj;
private:
};

// Configuration of a test case
template<class T, class D>
class unit_test : public configuration<T,D>
{
    public:
        unit_test() = delete;
        unit_test(custom_function<T,D> _func, const T &obj, const D &_data);
        unit_test(custom_function<T,D> _func,  T &&obj,  D &&_data);
        unit_test(const unit_test<T,D> &rhs) = default;
        unit_test(unit_test<T,D> &&rhs) = default;
        ~unit_test() = default;
        test_result start();

        // Return the result of the test
        const test_result& get_result() { result.name = this->name; return result; }
    protected:
        decltype(auto) commence_test(T &obj, D &data);
    private:
        test_result result;
};

#include "test_case.cpp"
#endif //SENTIMENTANALYSIS_TEST_CASE_H 

