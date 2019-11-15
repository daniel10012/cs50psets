
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Declaring the shift function
int shift(char c);

//Main function
int main(int argc, string argv[])
{
//Check if exactly 2 arg (launch and the key)
    if (argc == 2)
    {
        //check if each character of the key is alphabetic (hence negative numbers won't work)
        for (int i = 0, l = strlen(argv[1]); i < l; i++)
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        //Get the array of keys from the keyword
        int len_keys = strlen(argv[1]);
        int keys[len_keys];
        for (int i = 0; i < len_keys; i++)
        {
            keys[i] = shift(argv[1][i]);
            printf("%c", keys[i]);
        }

        //Get the secret message
        string plaintext = get_string("plaintext:");
        //Encoding message
        string ciphertext = plaintext;
        int n = 0;
        int k = 0;
        for (int i = 0, l = strlen(plaintext); i < l; i++)
        {
            //If character in plaintext is a letter (ASCII), shift it by the key
            char letter = plaintext[i];

            //Find the key if character is alphabetical
            if (isalpha(letter))
            {
                k = keys[n % len_keys];
                n++;
            }
            //Case where upper letter
            if (letter >= 65 && letter <= 90)
            {
                ciphertext[i] = (letter - 65 + k) % 26 + 65;
            }
            //Case where lower letter
            else if (letter >= 97 && letter <= 122)
            {
                ciphertext[i] = (letter - 97 + k) % 26 + 97;
            }
        }
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
//If less than 1 arg or more than 2 args, error
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

//Shift function
int shift(char c)
{
    int lower_char = tolower(c);
    return (lower_char - 97);
}