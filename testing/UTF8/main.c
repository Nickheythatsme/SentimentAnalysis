#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char f = 0;
    for (;f < 0xff; ++f)
        printf("%x\n", f);
    printf("%x\n", f);

}
