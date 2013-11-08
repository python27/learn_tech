#include <stdio.h>
#define IN 1
#define OUT 0

int main()
{
    int a[256];
    for (int i = 0; i < 256; ++i)
    {
        a[i] = 0;
    }

    int ch;
    int state = OUT;
    int cnt = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
            state = OUT;
            a[cnt]++;
            cnt = 0;
        }
        else 
        {
            if (state == OUT)
            {
                state = IN;
                cnt++;
            }
            else if (state == IN)
            {
                cnt++;
            }
        }
        
    }

    printf("words count:\n");
    for (int i = 0; i < 20; ++i)
    {
        printf(" %d", a[i]);
    }
    printf("\n");
    return 0;
}
