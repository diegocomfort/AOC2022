#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "day7.h"

#define BUFF_SIZE 256
#define INPUT_PATH "test.txt"


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
    fread(buff, sizeof(buff), SIZE, input);
    fclose(input);

    Directory *currentDirectory = NULL;

    // Read input
    for (long i = 0; i < SIZE; ++i)
    {
        while (buff[i] != '$') ++i;
        ++i;    // skip space between '$' and the command
        if (buff[i] == 'c') // cd
        {
            i += 3; // goto start of directory name
            // TODO:
        }
        else if (buff[i] == 'l') // ls
        {
            i += 3; // goto start of file size
            // TODO:
        }
        else continue;
    }


    // goto root (/)
    while (currentDirectory && currentDirectory->parentDirectory)
        currentDirectory = currentDirectory->parentDirectory;
    recursivelyFreeDirectory(currentDirectory);
    
    printf("Size of stdin: %lu\n", SIZE);

    return 0;
}