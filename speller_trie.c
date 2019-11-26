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
            unsigned int n = tolower(word[i]) - 'a';


            node *new_node = cursor->children[n];
            if (new_node == NULL)
            {
                 new_node = (node*) malloc(sizeof(node));
                 memset(new_node, 0, sizeof(node));
                 cursor->children[n] = new_node;
            }
            else
            {
                cursor = cursor->children[n];
            }
            if (i == l - 1)
            {
                cursor->is_word = true;
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
        unsigned int n = tolower(word[i]) - 'a';

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



