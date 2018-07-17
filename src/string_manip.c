#include "string_manip.h"

// Returns the length in the number of bytes of the current character
size_t char_len(signed char f)
{
    int i = 0;
    if (f >= 0)
    {
        return 1;
    }

    while (f < 0)
    {
        f <<= 1;
        ++i;
    }
    return i;
}

// Returns TRUE if this is a regular ascii char, false if otherwise
int ascii(signed char c)
{
    return c >= 0;
}

int test_char(const char *str, const char *delims)
{
    // Find the length of the character to test
    size_t s_len = char_len(*str);

    return test_char_n(str, delims, s_len);
}

int test_char_n(const char *str, const char *delims, int s_len)
{
    const char* d_str = delims; // delimiter string
    const char* str_head = str; // save the right character of str

    while ('\0' != *d_str)
    {
        // Find the length of the current delimiter character
        size_t d_len = char_len(*d_str);

        // Skip comparison if they're of different lengths
        if (d_len == s_len)
        {

            // accumulate the differences
            int diff = 0;
            for (int i = 0; i < d_len && 0 == diff; ++i, ++d_str, ++str) {
              diff += *d_str - *str;
            }

            // Return 1 if we have a match
            if (diff == 0) {
              return 1;
            }

            // reset str to the character we were testing
            str = str_head;
        }
        else
        {
            // Move along the delimiters if we're not comparing this character
            for (int i = 0; i < d_len; ++i) {
              ++d_str;
            }
        }
    }
    // Return false if we found no matches
    return 0;
}

// Return pos if delim is in str, (the equivolent to) -1 if it does not exist
size_t find(const char *str, const char *delim, size_t d_len)
{
    size_t s_len = strnlen(str, S_MAX);
    size_t i;

    for (i=0; i<s_len; ++i)
    {
        if (!strncmp(str, delim, d_len))
        {
            return i;
        }
        ++str;
    }
    return -1;
}

// Replace all chars from start to end with the delmiter character
// RETURNS a ptr to the next char (after the replacement)
char* replace(size_t start, size_t end, char *str, char delim)
{
    size_t i;
    char *current = &str[start];

    for (i=start; i<end && *current; ++i)
    {
        *current = delim;
        ++current;
    }
    return current;
}

// Remove all chars from start to end, then copy into a new character string
// RETURNS a ptr to the new string
char* remove_section(size_t start, size_t end, char *str)
{
    size_t s_len = strnlen(str, S_MAX) + 1;
    size_t s_len_diff = end - start;
    char *new_s = (char *) malloc(sizeof(char) * (s_len - s_len_diff));
    size_t i;

    for (i=0; i<start; ++i)
    {
        *new_s = str[i];
        ++new_s;
    }

    for (i=end; i<s_len; ++i)
    {
        *new_s = str[i];
        ++new_s;
    }
    return new_s;
}

// Replace all occurances of delim in str. Replaces with replace char
// RETURNS number of occurances of delim that were replaced
// wrapper
size_t replace_all(char *str, const char *delim, char replace_c)
{
    size_t d_len = strlen(delim);
    return replace_all_n(str, delim, replace_c, d_len);
}

// replace_all implementation
size_t replace_all_n(char *str, const char *delim, char replace_c, size_t d_len)
{
    size_t delim_loc = find(str, delim, d_len);
    size_t i;
    size_t delim_count = 0;

    while (delim_loc != S_FAIL)
    {
        str = &str[delim_loc];
        for (i=0; i<d_len; ++i)
        {
            *str = replace_c;
        }
        ++delim_count;
    }
    return delim_count;
}

// Remove all occurances of delim, then copy into a new character stringj
// RETURNS the number of occurrances removed
size_t remove_all(char *str, const char *delim)
{
    size_t d_len = strnlen(str, S_MAX);
    size_t removed = replace_all_n(str, delim, 0x01, d_len);

    size_t new_s_len = removed * d_len;
    char * new_s = (char*)malloc(sizeof(char) * new_s_len);

    // TODO finish copying over select parts of str into new_s
    return -1;

}
