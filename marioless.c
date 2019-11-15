// Abstraction and scope
#include <cs50.h>
#include <stdio.h>

// Indicating the function
int get_valid_height(string prompt);

// Main function
int main(void)
{
    int n = get_valid_height("Height: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = n-i-1; j > 0; j--)
        {
            printf(" ");
        }
        for (int x = 0; x <= i; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Prompt user for valid height
int get_valid_height(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while ((n < 1)||(n > 8));
    return n;
}
