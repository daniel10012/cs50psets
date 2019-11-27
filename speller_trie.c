// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


// Represents number of children for each node in a trie
#define N 27
unsigned int words = 0;

// Prototype for index function
unsigned int index(char c);

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// declare free node function
void clear(node *ptr);

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        words ++;
        node *cursor = root;
        for (int i = 0, l = strlen(word); i < l; i++)
        {
            unsigned int n = index(word[i]);

            node *next_node = cursor->children[n];
            if (next_node == NULL)
            {
                 next_node = malloc(sizeof(node));
                 if (next_node == NULL)
                 {
                     return false;
                 }
                 next_node->is_word = false;
                 for (int j = 0; j < N; j++)
                 {
                     next_node->children[j] = NULL;
                 }
                 cursor->children[n] = next_node;
                 if (i == l - 1)
                 {
                     cursor->is_word = true;
                 }
                 cursor = next_node;
            }
            else
            {
                if (i == l - 1)
                {
                    cursor->is_word = true;
                }
                cursor = cursor->children[n];
            }



        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = root;

    for (int i = 0, l = strlen(word); i < l; i++)
    {
        unsigned int n = index(word[i]);

        if (cursor->children[n] == NULL)
        {
            return false;
        }

        if (i == l - 1)
        {
            if (cursor->is_word == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        cursor = cursor->children[n];
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    clear(root);
    return true;
}


//function to clear a node
void clear(node *ptr)
{
    for (int i = 0; i < N; i++)
    {
        if (ptr->children[i] != NULL)
        {
            clear(ptr->children[i]);
        }
    }
    free(ptr);
}

// Function to get the index of a letter or '\''
unsigned int index(char c)
    {
        unsigned int n;
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
        {
            n = tolower(c) - 'a';
        }
        else if (c == '\'')
        {
            n = 26;
        }
        else
        {
            n = 1000;
        }
        return n;
    }
