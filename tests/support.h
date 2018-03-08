//
// Created by njgro on 3/7/2018.
//
#include <iostream>
#include <fstream>
#include <cstring>

#ifndef SENTIMENTANALYSIS_SUPPORT_H
#define SENTIMENTANALYSIS_SUPPORT_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINPAUSE system("pause");
#else
#define WINPAUSE
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::cin;

// General support functions to get the file contents
bool get_path(char *&path, const char *message);
long read_file(const char *filename, char *&buff);

// General testing functions
template <class T> bool test_object(T &object);
template <class T> bool test_copy(T &object);
template <class T> bool test_move(T &object);
template <class T> bool test_assignment(T &object);



#include "support.cpp"
#endif //SENTIMENTANALYSIS_SUPPORT_H
