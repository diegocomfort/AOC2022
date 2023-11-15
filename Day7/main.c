#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "day7.h"

#define INPUT_PATH "test.txt"

int main(void)
{
    printf(INPUT_PATH"\n");
    
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
        return 1;

    // Get size of file 
    fseek(input, 0L, SEEK_END);
    const long SIZE = ftell(input) + 1;
    rewind(input);
    printf("Read size of "INPUT_PATH": %li\n", SIZE);

    char *buff = malloc((size_t) SIZE * sizeof(char));
    fread(buff, sizeof(buff), (size_t) SIZE, input);
    fclose(input);
    printf("Read "INPUT_PATH" into a buffer\n");

    // Directory *currentDirectory = NULL;

    // Read input
    for (long i = 0; i < SIZE; ++i)
    {
        putchar(buff[i]);
        // while (buff[i] != '$') ++i;
        // ++i;    // skip space between '$' and the command
        // if (buff[i] == 'c') // cd
        // {
        //     i += 3; // goto start of directory name
        //     // TODO:
        // }
        // else if (buff[i] == 'l') // ls
        // {
        //     i += 3; // goto start of file size
        //     // TODO:
        // }
        // else continue;
    }
    free(buff);


    // goto root (/)
    // while (currentDirectory && currentDirectory->parentDirectory)
    //     currentDirectory = currentDirectory->parentDirectory;
    // recursivelyFreeDirectory(currentDirectory);
    
    return 0;
}
