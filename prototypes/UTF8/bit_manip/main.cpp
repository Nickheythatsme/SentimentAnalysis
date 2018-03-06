#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>


using namespace std;

int char_len(signed char f)
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

void display_char(const char *c)
{
    int len = char_len(*c);
    for(; len >= 0; --len)
    {
        printf("%c",*c);
        ++c;
    }
    fflush(stdout);
}


char* next_char(char *buff, bool show)
{
    int len = char_len(*buff);
    for (;len >= 0; --len)
    {
        if(show)
            printf("%c",*buff);
        ++buff;
    }
    return buff;
}

int char_cmp(const char *str, const char *to_test)
{
    int str_len = char_len(*str);
    int to_test_len = char_len(*to_test);

    if (str_len != to_test_len)
        return 0;
    for (;str_len >= 0; --str_len)
    {
        if (*str != *to_test)
            return 0;
        ++str;
        ++to_test;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./a.out [filename]" << endl;
        exit(EXIT_FAILURE);
    }
    ifstream fin(argv[1]);
	if (!fin)
		exit(EXIT_FAILURE);
    int len;
    char *buff;
    char *temp;

    fin.seekg (0, fin.end);
    len = fin.tellg();
    fin.seekg (0, fin.beg);

    cout << len << endl;
    buff = new char[len + 1];

    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');
    temp = buff;

    char to_test[] = "‹";
    while(buff && *buff)
    {
        display_char(buff);
        buff = next_char(buff, false);
    }

    printf("\n\n");
    buff = temp;
    while(buff && *buff)
    {
        if (char_cmp(buff, to_test))
        {
            printf("MATCH: ");
            display_char(buff);
        }
        buff = next_char(buff, false);
    }
    printf("\n\n");

    delete [] temp;
}
