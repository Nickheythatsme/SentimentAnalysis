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

// lowercases all ascii letters
void lower(char *s)
{
    while(*s)
    {
        if (*s >= 'A' && *s <= 'Z')
        {
            *s += 32;
        }
    }
}

// Return pos if delim is in str, (the equivolent to) -1 if it does not exist
size_t find(const char *str, const char *delim, size_t d_len)
{
    size_t i=0;
    while (*str)
    {
        if (!strncmp(str, delim, d_len))
        {
            return i; 
        }
        ++str;
        ++i;
    }
    return S_FAIL;
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

// replace_all implementation
size_t _replace_all(char *str, const char *delim, char replace_c, size_t d_len)
{
    size_t i;
    size_t result = find(str, delim, d_len);

    if (result == S_FAIL)
    {
        return 0;
    }

    for (i=result; i<result + d_len; ++i)
    {
        str[i] = replace_c;
    }

    return _replace_all(str, delim, replace_c, d_len) + 1;
}

// Replace all occurances of delim in str. Replaces with replace char
// RETURNS number of occurances of delim that were replaced
// wrapper
size_t replace_all(char *str, const char *delim, char replace_c)
{
    size_t d_len = strlen(delim);
    return _replace_all(str, delim, replace_c, d_len);
}

// Remove all occurances of delim, then copy into a new character stringj
// RETURNS the number of occurrances removed
char* remove_all(const char *str, const char *delim)
{
    size_t d_len = strnlen(delim, S_MAX);
    size_t count = 0;
    size_t result = find(str, delim, d_len);
    const char *str_head = str;

    while (result != S_FAIL)
    {
        ++count;
        str += sizeof(char) * result + 1;
        result = find(str, delim, d_len);
    }

    size_t new_s_bytes = sizeof(char) * (strnlen(str_head, S_MAX) + 1 - (count * d_len));
    char * new_s = (char*)malloc(new_s_bytes);
    _remove_all(str_head, delim, d_len, new_s);
    return new_s;
}

// Remove all implementation
void _remove_all(const char *str, const char *delim, size_t d_len, char *dest)
{
    while (!strncmp(str, delim, d_len))
    {
        str += sizeof(char) * d_len;
    }
    while(*str)
    {
        *dest = *str;
        ++str; ++dest;
        while (!strncmp(str, delim, d_len))
        {
            str += sizeof(char) * d_len;
        }
    }
    *dest = '\0';
    return;
}
