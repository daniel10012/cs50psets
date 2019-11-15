#include <stdio.h>


int main(void)
{
    int n = 10;
    int result = 1;
    while (n > 0)
    {
        result *= n;
        n--;
    }
    printf("%i\n", result);
}