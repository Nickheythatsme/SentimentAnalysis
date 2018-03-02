#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

#define MAX_LEN 1024

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

void copy_character(const char *str, char *buff, int char_len, int buff_index)
{
	for (; char_len > 0 && buff_index < MAX_LEN && *str; --char_len)
	{
		*buff = *str;
		++buff; ++str;
	}
    *buff = '\0';
}

int main(int argc, char **argv)
{
    char buff[1024];
    int len = char_len(*argv[1]);

    copy_character(argv[1], buff, len, 0);
    cout << buff << endl;
}
