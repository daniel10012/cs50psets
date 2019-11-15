#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
//Check if exactly 2 arg (launch and the key)
    if (argc == 2)
    {
        //check if each character of the key is a digit (hence negative numbers won't work)
        for (int i = 0, l = strlen(argv[1]); i < l; i++)
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        //Convert the input "string number" to a number
        int k = atoi(argv[1]);
        //Get the secret message
        string plaintext = get_string("plaintext:");
        //Encoding message
        string ciphertext = plaintext;
        for (int i = 0, l = strlen(plaintext); i < l; i++)
        {
            //If character in plaintext is a letter (ASCII), shift it by the key
            char letter = plaintext[i];
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