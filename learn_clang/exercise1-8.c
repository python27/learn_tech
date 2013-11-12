#include <stdio.h>

int main()
{
    int nb = 0, nt = 0, nl = 0;
    int ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ')
        {
            nb++;
        }
        else if (ch == '\t')
        {
            nt++;
        }
        else if (ch == '\n')
        {
            nl++;
        }
    }

    printf("%d %d %d\n", nb, nt, nl);
    return 0;
}
