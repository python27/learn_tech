#include <stdio.h>
#include <stdlib.h>


int main()
{
    int ch;
    int isFirstBlank = 1;
    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' && isFirstBlank)
        {
            putchar(ch);
            isFirstBlank = 0;
        }

        if (ch != ' ')
        {
            putchar(ch);
            isFirstBlank = 1;
        }
    }
    printf("\n");


    return 0;
}
