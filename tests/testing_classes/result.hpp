#include <chrono> // For tracking execution time
#include <ostream> // Outputting results to ostream
#include <exception>
#include <string> // Aid in outputting results to stream
#include <ctime> // For displaying the time

#ifndef SENTIMENTANALYSIS_TESTING_RESULT
#define SENTIMENTANALYSIS_TESTING_RESULT

using std::chrono::system_clock;

// Result of a test. Also formats the display
class general_result 
{
public:
    general_result() = default;
    general_result(const general_result &rhs) = default;
    general_result(general_result &&rhs) = default;
    ~general_result() = default;
    general_result& operator=(const general_result &_general_result) = default;
    general_result& operator=(general_result &&_general_result) = default;

    bool passed {false};
    std::string name;
    size_t iterations {0};
    system_clock::time_point beginning;
    system_clock::time_point ending;
    std::chrono::duration<double> average {0};
    std::chrono::duration<double> total {0};

    friend std::ostream& operator<<(std::ostream& out, const general_result &rhs);
protected:
    std::ostream& display(std::ostream& out) const; 
    static std::string display_time(const std::chrono::duration<double> &t);
    static std::string display_time(const system_clock::time_point &t);
};

/* general_result implementation */
// output to a stream
std::ostream& operator<<(std::ostream& out, const general_result &rhs)
{
    return rhs.display(out);
}

// Format the output and return the ostream object
std::ostream& general_result::display(std::ostream& out) const
{
    out << "Test name: " << name << std::endl
        << "\tPassed: " << passed << std::endl
        << "\tIterations completed: " << iterations << std::endl
        << "\tStart time: " << display_time(beginning) << std::endl
        << "\tEnd time: " << display_time(ending) << std::endl
        << "\tAverage exec time: " << display_time(average) << std::endl
        << "\tTotal exec time:   " << display_time(total);
    return out;
}

// format the time and return it as a string
std::string general_result::display_time(const std::chrono::duration<double> &t)
{
    // Find the integer value of each hour/min/sec/etc
    auto hours = std::chrono::duration_cast<std::chrono::hours>(t).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(t).count() % 60;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(t).count() % 60;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t).count() % 1000; 
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(t).count() % 1000;
    std::string to_ret;

    if (hours < 10) to_ret.append("0");
    to_ret.append(std::to_string(hours) + ":");

    if (minutes < 10) to_ret.append("0");
    to_ret.append(std::to_string(minutes) + ":");

    if (seconds < 10) to_ret.append("0"); 
    to_ret.append(std::to_string(seconds) + " ");

    to_ret.append(std::to_string(milliseconds) + "ms ");
    to_ret.append(std::to_string(microseconds) + "ms ");

    return to_ret;
}

// Convert the time started and finished to a string and return it
std::string general_result::display_time(const system_clock::time_point &t)
{
    const auto converted_time = system_clock::to_time_t(t);
    std::string ret_string {ctime(&converted_time)};
    ret_string.erase(ret_string.size()-1, 1);
    return ret_string;
}

#endif // SENTIMENTANALYSIS_TESTING_RESULT