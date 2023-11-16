#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "day7.h"

#define INPUT_PATH "test.txt"

int main(void)
{
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
        return 1;

    // Get size of file 
    fseek(input, 0L, SEEK_END);
    const size_t fileSize = (size_t) ftell(input);
    rewind(input);

    printf("Size of file: %lu\n", fileSize);

    char *buff = malloc(fileSize * sizeof(char));
    if (buff == NULL)
        return 2;
    fread(buff, sizeof(char), (size_t) fileSize, input);
    fclose(input);

    char *rootString = malloc(2UL);
    rootString[0] = '/';
    rootString[1] = 0;

    Directory *root = createDirectory(rootString);
    Directory *currentDirectory = root;
    printDirectory(currentDirectory);

    // Read input
    for (char *currentChar = buff; 
         currentChar < buff + fileSize; 
         ++currentChar)
    {
        // Goto next '$' (start of command)
        while (currentChar < buff + fileSize && 
               *currentChar != '$') ++currentChar;
        if (currentChar >= buff + fileSize - 1) break;
        
        currentChar += 2; // skip space between '$' and the command

        // cd command
        if (*currentChar == 'c')
        {
            // goto start of directory name
            currentChar += 3;
            // Get directory name
            char *endOfDirName = currentChar;
            while (!isspace(*(endOfDirName + 1)))
                ++endOfDirName;

            char *directoryName = substring(currentChar, endOfDirName);
            if (directoryName == NULL)
            {
                recursivelyFreeDirectory(root);
                return -1;
            }

            // Go to root
            if (directoryName[0] == '/')
            {
                currentDirectory = root;
                free(directoryName);
            }
            // Go to ../ (parent directory)
            else if (directoryName[0] == '.' && directoryName[1] == '.')
            {
                if (currentDirectory->parentDirectory)
                    currentDirectory = currentDirectory->parentDirectory;
                free(directoryName);
            }
            // Create new directory
            else 
            {
                Directory *directory = createDirectory(directoryName);
                appendDirectory(currentDirectory, directory);
                currentDirectory = directory;
            }

            //printDirectory(currentDirectory);
            
        }
        // ls command
        else if (*currentChar == 'l')
        {
            currentChar += 3; // goto start of file size
            char *endOfFileSize = currentChar;
        }
        else continue;
    }

    printDirectory(root);
    printDirectory(root->subDirectories[0]);

    free(buff);
    recursivelyFreeDirectory(root);
    
    return 0;
}
