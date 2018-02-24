#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

int char_len(unsigned char f)
{
    if (f >> 7 == 0)
        return 1;
    else if (f >> 5 == 0x6)
        return 2;
    else if (f >> 4 == 0xe)
        return 3;
    else if (f >> 3 == 0x1e)
        return 4;

    return -1;
}

char* next_char(char *buff)
{
    int len = char_len(*buff);
    if (len < 0)
    {
        printf("ERROR: %x\n", *buff);
        return ++buff;
    }
    for (;len >= 0; --len)
    {
        printf("%c",*buff);
        ++buff;
    }
    return buff;
}

int test_char(char *str, char *to_test)
{
    if (!str) return -1;
    int diff = 0;
    auto len_str = char_len(*str);
    auto len_to_test = char_len(*to_test);
    if (len_str < 0 || len_to_test < 0) return -1;

    if (len_str != len_to_test) return 0;

    for (;len_str >= 0; --len_str)
    {
        if (0 != *str - *to_test)
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

    fin.seekg (0, fin.end);
    len = fin.tellg();
    fin.seekg (0, fin.beg);

    cout << len << endl;
    buff = new char[len + 1];

    fin.get(buff, len, '\0');
    fin.ignore(len, '\0');

    char to_test[] = "™";
    while(buff && *buff)
    {
        /*
        if (test_char(buff,to_test) == 1)
            cout << "Buff same as to_test" << endl;
        */
        buff = next_char(buff);
    }

}
