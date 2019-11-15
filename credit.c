//Include libraries
#include <cs50.h>
#include <stdio.h>

//declare functions
long get_number(string prompt);
int count_digits(long n);

//Main function
int main(void)
{
   long n = get_number("number:");
   int c = count_digits(n);

   //Return INVALID if number of digits not correct
   if ( ( c < 13 ) || ( c > 16) || ( c == 14) )
   {
       printf("INVALID\n");
   }
   else
   {
       long i = 1;
       int counter = 0;
       int sum = 0;
       while ( count_digits(i) < c + 1 )
       {
           int num_to_add = n % (10 * i) / i;
           i *= 10;
           //Adding the digits of double of numbers starting before the last one
           if (counter % 2 == 1)
           {
               num_to_add *= 2;
               if ( num_to_add > 9)
               {
                  num_to_add = num_to_add % 10 + (num_to_add % 100) / 10;
               }

           }
           //Adding all numbers
           sum += num_to_add;
           counter++;
         }

       //Verifying the checksum ends by 0
       if (sum % 10 == 0)
       {
           if ( ( ( c == 13 ) || ( c == 16 ) ) && ( n /  ( i / 10 ) == 4 ))
           {
               printf("VISA\n");
           }
           else if ( ( c == 15 ) && ( ( n /  ( i / 100 ) == 34 ) ||  (n /  ( i / 100 ) == 37 )))
           {
               printf("AMEX\n");
           }
           else if ( ( c == 16 ) && ( ( n /  ( i / 100 ) == 51 ) ||  (n /  ( i / 100 ) == 52 ) || (n /  ( i / 100 ) == 53 ) || (n /  ( i / 100 ) == 54 ) || (n /  ( i / 100 ) == 55 ) ))
           {
               printf("MASTERCARD\n");
           }
           else
           {
               printf("INVALID\n");
           }
        }
       else
       {
           printf("INVALID\n");
       }
   }
}

//Get cc number
long get_number(string prompt)
{
    long n;
    do
    {
        n = get_long("%s",prompt);
    }
    while ( n < 0 );
    return n;
}

//Count digits
int count_digits(long n)
{
    int counter = 0;
    while ( n > 0 )
    {
        n /= 10;
        counter ++;
    }
    return counter;
}