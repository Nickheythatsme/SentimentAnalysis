//
// Created by njgro on 3/9/2018.
//
#include <cstring>
#include <cctype>

#ifndef SENTIMENTANALYSIS_UTF8_MANIP_H
#define SENTIMENTANALYSIS_UTF8_MANIP_H

/*
 * So for UTF-8 encoding:
 *  0x00 - 0x7f is regular 1 byte ASCII character
 *  0x80 - 0xBF means this is a continuing byte for a multi-byte character
 *  0xC2 - 0xDF is the beginning byte of a two byte character
 *  0xE0 - 0xEF is the beginning byte of a three byte character
 *  0xF0 - 0xFF is the beginning byte of a four byte sequence
 *
 *  len      1st byte
 *  1 bytes  0xxxxxxx
 *  2 bytes  110xxxxx
 *  3 bytes  1110xxxx
 *  4 bytes  11110xxx
 */

class utf8_manip
{
public:
    utf8_manip() = default;
    utf8_manip(const utf8_manip &obj) = default;
    ~utf8_manip() = default;

    // Returns true if it is a regular ascii
    // Returns false if it is a special UTF8 character
    static int ascii(signed char c);

    // Wrapper for other test_character function(char*, char*, int)
    static int test_character(const char *str, const char *delims);

    // Test the current character to another character, or to a set of delimiters
    // RETURNS false if str is NOT in delims, true if otherwise
    static int test_character(const char *str, const char *delims, int len);

    // Return the length of the character (1 byte for ascii, more than one for special UTF8)
    static int character_length(signed char f);

    // Copy the character from str into buff, with max_len being a limiter
    // Returns 1 if copy was successful, 0 if the character was too long
    static int copy_character(const char *str, char *buff, int max_len=4);

    // Copy the character from str into buff but do NOT look up the char len again
    static int copy_character(const char *str, char *buff, int max_len, int char_len);

    // Move the character string onto the next character
    static const char* next_character(const char *str);
protected:
private:
};


#endif //SENTIMENTANALYSIS_UTF8_MANIP_H
