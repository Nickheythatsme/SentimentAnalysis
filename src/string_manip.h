#include <string.h>
#include <stdlib.h>

#ifndef SENTIMENTANALYSIS_STRING_MANIP_
#define SENTIMENTANALYSIS_STRING_MANIP_

#define S_MAX 8589934592
#define S_FAIL -1lu
#define REPLACE_DELIM 0x7f

struct remove_loc
{
    size_t len;
    size_t pos;
    struct remove_loc *next;
};

/**** UTF MANIPULATION functions ****/

// Returns true if it is a regular ascii
// Returns false if it is a special UTF8 character
int ascii(signed char c);

// Return the length of the character (1 byte for ascii, more than one for special UTF8)
size_t char_len(signed char f);

// lowercases all ascii letters
void lower(char *s);

/**** PARSING STRING MANIPULATION ****/

// Find the first occurance of delim.
// Returns starting location of delim if found
// OR S_FAIL if not found
size_t find(const char *str, const char *delim, size_t d_len);
size_t find_all(const char *str, const char *delim, size_t d_len, struct remove_loc **locations);

// Remove all occurances of delim, then copy into a new character string
// RETURNS the number of occurrances removed
char* remove(const char *str, const char *delim);
void _remove(const char *str, const char *delim, size_t d_len, char *dest);

char* remove_all(const char *str, const char **delim, size_t delim_count);

#endif // SENTIMENTANALYSIS_STRING_MANIP_
