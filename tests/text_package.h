//
// Created by njgro on 3/7/2018.
//
#include <iostream>
#include <exception>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <glob.h>

#ifndef SENTIMENTANALYSIS_TEXT_PACKAGE_H
#define SENTIMENTANALYSIS_TEXT_PACKAGE_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINPAUSE system("pause");
#else
#define WINPAUSE
#endif

using std::cerr;
using std::endl;
using std::cin;
using std::string;

// Handle errors while assembling the package
class text_package_error : public std::exception
{
public:
    text_package_error() noexcept;
    text_package_error(string message, string dirname="", string filename="") noexcept;
    string message;
    string dirname {"no dir specified"};
    string filename{"no filename specified"};
    friend std::ostream& operator<<(std::ostream& out, const text_package_error &rhs);
};

// This is used to wrap a bunch of text files
class text_package : public std::vector<string>
{
    public:
        text_package() = delete;
        text_package(string dirname);
        ~text_package() = default;
        size_t bytes() {return _bytes;}
    private:
        size_t load_files();
        size_t load_files(glob_t *globbed);
        static int glob_error(const char *path, int errno);
        string dirname;
        size_t _bytes;

        // General support functions to get the file contents
        static long read_file(const string &filename, string &buff);
};

#endif //SENTIMENTANALYSIS_SUPPORT_H