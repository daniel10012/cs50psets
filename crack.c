#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    //Check if user gave 1 hash
    if (argc == 2)
    {
        string hash = argv[1];
        //Getting the salt from the hashed password
        char salt[3];
        salt[0] = hash[0];
        salt[1] = hash[1];
        salt[2] = '\0';

        //Trying every guess possible from 1 letter to 5 letters
        string alphachars = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int l = 53;
        char tentative_password[6] = "\0\0\0\0\0\0";

        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < l; j++)
            {
                for (int k = 0; k < l; k++)
                {
                    for (int m = 0; m < l; m++)
                    {
                        for (int n = 1; n < l; n++)
                        {
                            //Inner loop start first and loops stop when encountering \0
                            //This gets us all word possibilities from a to ZZZZ
                            tentative_password[0] = alphachars[n];
                            tentative_password[1] = alphachars[m];
                            tentative_password[2] = alphachars[k];
                            tentative_password[3] = alphachars[j];
                            tentative_password[4] = alphachars[i];
                            //Comparing the value (not location) of the hashed tentative password and
                            //hash provided
                            if (strcmp(crypt(tentative_password, salt), hash) == 0)
                            {
                                //If they're equal we return the cracked password
                                printf("%s\n", tentative_password);
                                return 0;
                            }


                        }
                    }
                }
            }
        }
        //If all possibilities didn't return a match, there is no corresponding password to the hash
        //that is less than 5 letters
        printf("Password not found");
        return 404;
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}