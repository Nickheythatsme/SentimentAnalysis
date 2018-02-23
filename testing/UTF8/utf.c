#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    int val;
    char str[sizeof(val) + 1];
    sscanf(argv[1],"%x",val);
}
