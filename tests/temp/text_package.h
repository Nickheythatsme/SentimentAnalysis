//
// Created by njgro on 3/7/2018.
//
#include <iostream>
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

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;

// This is used to wrap a bunch of text files
class text_package : public std::vector<string>
{
    public:
        text_package() = delete;
        text_package(const string &dirname);
        ~text_package();
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