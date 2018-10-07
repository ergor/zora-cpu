
#include <stdio.h>
#include "ctrl_lines.h"

void test(int a, int b, int c)
{
    printf("%d, %d, %d", a, b, c);
}

int main(int argc, char** argv)
{
    //test(TEST);
    for (int i = 0; i < DATA_LN_CNT; i++)
        printf("%d\n", pols[i]);
    return 0;
}