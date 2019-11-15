//Include libraries
#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Input function
float get_change(string prompt);

//Main function
int main(void)
{
    float i = get_change("Change owed:");
    int cents = round(i * 100);
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    int change_left = cents;
    int coin_count = 0;
    while ( change_left > 0 )
    {
        quarters = change_left / 25;
        dimes = change_left / 10;
        nickels = change_left / 5;
        pennies = change_left / 1;

        if ( quarters > 0 )
        {
            change_left -= quarters * 25;
            coin_count += quarters;
        }
        else if ( dimes > 0 )
        {
            change_left -= dimes * 10;
            coin_count += dimes;
        }
        else if ( nickels > 0 )
        {
            change_left -= nickels * 5;
            coin_count += nickels;
        }
        else if ( pennies > 0 )
        {
            change_left -= pennies;
            coin_count += pennies;
        }
    }

    printf("%i\n",coin_count);
}


//Change input function
float get_change(string prompt)
{
    float n;
    do
    {
        n = get_float("%s",prompt);
    }
    while ( n < 0 );
    return n;
}