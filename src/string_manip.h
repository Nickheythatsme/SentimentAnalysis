#include <string.h>
#include <stdlib.h>

#ifndef SENTIMENTANALYSIS_STRING_MANIP_
#define SENTIMENTANALYSIS_STRING_MANIP_

#define S_MAX 2048
#define S_FAIL -1lu

/**** UTF MANIPULATION functions ****/

// Returns true if it is a regular ascii
// Returns false if it is a special UTF8 character
int ascii(signed char c);

// Return the length of the character (1 byte for ascii, more than one for special UTF8)
size_t char_len(signed char f);

/**** PARSING STRING MANIPULATION ****/
// Return starting location of first delim if delim is in str, 
// -1 if it does not exist
size_t find(const char *str, const char *delim, size_t d_len);

// Replace all chars from start to end with the delmiter character
// RETURNS a ptr to the next char (after the replacement)
char* replace(size_t start, size_t end, char *str, char delim);

// Remove all chars from start to end, then copy into a new character string
// RETURNS a ptr to the new string
char* remove_section(size_t start, size_t end, char *str);

// Replace all occurances of delim in str. Replaces with replace char
// RETURNS number of occurances of delim that were replaced
size_t replace_all(char *str, const char *delim, char replace_c);
// replace_all implementation
size_t _replace_all(char *str, const char *delim, char replace_c, size_t d_len);

// Remove all occurances of delim, then copy into a new character string
// RETURNS the number of occurrances removed
size_t remove_all(char *str, const char *delim);

#endif // SENTIMENTANALYSIS_STRING_MANIP_
