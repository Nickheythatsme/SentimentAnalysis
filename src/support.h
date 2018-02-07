#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <glob.h>
#include <unistd.h>

using std::string;

// HTML tags that should be cleaned
static const char *to_clean[] = {"<br />","<br >"};
static uint to_clean_count = sizeof(to_clean) / sizeof(char *);

/* File I/O and support functions */
string read_file(char *fname);
std::vector<string> glob_files(const char *dir_name);

/* Cleaning functions */
void lower(string &word);
void replace(string &str);
void clean(string &word);
