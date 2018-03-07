//
// Created by njgro on 3/7/2018.
//
#include <iostream>
#include <fstream>
#include <cstring>

#undef DEFAULT_PATH
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINPAUSE system("pause");
#else
#define WINPAUSE
#endif

using std::cout;
using std::endl;
using std::cin;

// Forward declaration of support functions
bool get_path(char *&path, const char *message);
long read_file(const char *filename, char *&buff);

#ifndef SENTIMENTANALYSIS_SUPPORT_H
#define SENTIMENTANALYSIS_SUPPORT_H



#endif //SENTIMENTANALYSIS_SUPPORT_H
