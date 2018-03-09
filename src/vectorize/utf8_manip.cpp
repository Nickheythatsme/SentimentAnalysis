//
// Created by njgro on 3/9/2018.
//

#include "utf8_manip.h"

// Returns the length in the number of bytes of the current character
int utf8_manip::character_length(signed char f)
{
    int i = 0;
    if (f >= 0)
        return 1;

    while (f < 0)
    {
        f <<= 1;
        ++i;
    }
    return i;
}

// Returns TRUE if this is a regular ascii char, false if otherwise
int utf8_manip::ascii(signed char c)
{
    return c >= 0;
}

int utf8_manip::test_character(const char *str, const char *delims)
{
    // Find the length of the character to test
    int s_len = character_length(*str);

    return test_character(str, delims, s_len);
}

int utf8_manip::test_character(const char *str, const char *delims, int s_len)
{
    const char *d_str = delims; // delimiter string
    const char *str_head = str; // save the right character of str

    while (*d_str)
    {
        // Find the length of the current delimiter character
        int d_len = character_length(*d_str);

        // Skip comparison if they're of different lengths
        if (d_len == s_len)
        {

            // accumulate the differences
            int diff = 0;
            for (int i=0; i<d_len && 0 == diff; ++i, ++d_str, ++str)
                diff += *d_str - *str;

            // Return 1 if we have a match
            if (diff == 0)
                return 1;

            // reset str to the character we were testing
            str = str_head;
        }
        else
        {
            // Move along the delimiters if we're not comparing this character
            for(int i=0; i < d_len; ++i)
                ++d_str;
        }
    }
    // Return false if we found no matches
    return 0;
}

// wrapper for copy_character function
int utf8_manip::copy_character(const char *str, char *buff, int max_len)
{
    int char_len = character_length(*str);
    return copy_character(str, buff, max_len, char_len);
}
// Copy a character of length char_len from str into buff.
// Returns false if max_len > char_len
int utf8_manip::copy_character(const char *str, char *buff, int max_len, int char_len)
{
    if (char_len >= max_len) return 0;

    for (;char_len >=0 && *str; --char_len)
    {
        *buff = *str;
        ++str;
        ++buff;
    }
    *buff = '\0';
    return char_len;
}
