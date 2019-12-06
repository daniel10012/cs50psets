// include libraries
#include <cs50.h>
#include <stdio.h>

// declare functions
int get_valid_int(string prompt);

//main function
int main(void)
{
    int n = get_valid_int("Positive integer between 1 and 8: ");

    for (int i = 0; i < n; i++)
    {
        int j = (n - i);
        for (int x = 1; x < j; x++)
        {
            printf(" ");
        }
        for (int y = n - i ; y < n+1; y++)
        {
            printf("#");
        }
        printf("  ");
        for (int y = n - i ; y < n+1; y++)
        {
            printf("#");
        }
        printf("\n");
    }

}

// Prompt user for positive integer between 1 and 8 inclusive
int get_valid_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while ( (n < 1) || (n > 8) );
    return n;
}

#
