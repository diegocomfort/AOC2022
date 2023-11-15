#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "day7.h"

#define BUFF_SIZE 256
#define INPUT_PATH "input.txt"


int main(void)
{
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
        return 1;

    // Get size of stdin
    fseek(input, 0L, SEEK_END);
    const long SIZE = ftell(input) + 1;
    rewind(input);

    char buff[SIZE];
    long i = 0;


    // Create root directory
    char *rootStr = malloc(2 * sizeof(char));
    if (rootStr == NULL) return 2;
    rootStr[0] = '/';
    rootStr[1] = 0;
    Directory *root = createDirectory(rootStr);
    if (root == NULL)
    {
        free(rootStr); 
        return 3;
    }
    
    Directory *currentDirectory = root;

    for (; i < SIZE; ++i)
    {
        while (buff[i] != '$') ++i;
        ++i;    // skip space between '$' and the command
        if (buff[i] == 'c') // cd
        {

        }
        else if (buff[i] == 'l') // ls
        {

        }
        else break;
    }
    
    fclose(input);

    printf("Size of stdin: %lu\n", SIZE);

    return 0;
}