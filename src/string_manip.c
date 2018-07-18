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

size_t find_all(const char *str, const char *delim, size_t d_len, struct remove_loc **locations)
{
    size_t result = find(str, delim, d_len);

    if (S_FAIL == result)
    {
        *locations = NULL;
        return 0;
    }
    *locations = (struct remove_loc*) malloc(sizeof(struct remove_loc));
    (*locations)->len = d_len;
    (*locations)->pos = result;

    return find_all(&str[result + 1], delim, d_len, &(*locations)->next) + d_len;
}

void sort_lll(struct remove_loc **head)
{
    if (!*head->next) return;
    if (*head->next->loc < *head->loc)
    {
        // TODO finish sort
        struct remove_loc *temp = *head->next;
        *head->next = *head->next->next;
    }
}

// Remove all occurances of delim, then copy into a new character stringj
// RETURNS the number of occurrances removed
char* remove(const char *str, const char *delim)
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
    _remove(str_head, delim, d_len, new_s);
    return new_s;
}

// Remove all implementation
void _remove(const char *str, const char *delim, size_t d_len, char *dest)
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

char* remove_all(const char *str, const char **delims, size_t delim_count)
{
    size_t bytes_replaced = 0;
    size_t str_len = strnlen(str, S_MAX);
    size_t i;
    struct remove_loc *head;

    for (i=0; i<delim_count; ++i)
    {
        bytes_replaced += find_all(str, delims[i], strnlen(delims[i], S_MAX), &head);
    }
    char * new_s = (char *)malloc(sizeof(char) * (str_len - bytes_replaced + 1));

    struct remove_loc *current = head;
    while (current)
    {
        printf("len: %lu\tLocation: %lu\n", current->len, current->pos);
        current = current->next;
    }
    printf("bytes replaced: %lu\n", bytes_replaced);

    return NULL;
}

int main(int argc, char **argv)
{
    char to_test[] = "this is an example phrase! test is an example here!";
    printf("%s\n", to_test);
    remove_all(to_test, &(argv[1]), argc - 1);
    return 0;
}
