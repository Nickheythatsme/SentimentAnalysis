#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <glob.h>
#include <unistd.h>

using std::string;

/* File I/O and support functions */
string read_file(char *fname);
std::vector<string> glob_files(const char *dir_name);
void replace(string &str);
void clean_files(std::vector<string> &words);
