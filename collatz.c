#include <stdio.h>


int col(int n);


int main(void)
{
    int n = 7;
    printf("%i\n", col(n));
}


int col(int n)
{
    if (n == 1)
    {
        return 0;
    }
    else if (n % 2 == 0)
    {

        return 1 + col(n/2);
    }
    else
    {
        return 1 + col(3 * n + 1);
    }
}