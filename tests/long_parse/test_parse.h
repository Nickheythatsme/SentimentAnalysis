#include <iostream>
#include <cstring>
#include <chrono>
#include "parse.h"
#include "../support.h"

#ifndef S_PARSE_TEST
#define S_PARSE_TEST

bool test_parse(const char *text);
bool parse_text(text_package &a);

#include "test_parse.cpp"
#endif //S_PARSE_TEST

