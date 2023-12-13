#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "day7.h"

#define INPUT_PATH              "input.txt"
#define MAXIMUM_DIRECOTRY_SIZE  100000UL
#define TOTAL_DISK_SPACE        70000000UL
#define DISK_SPACE_NEADED_FREE  30000000UL

int partOne(void);
int partTwo(void);

int main(void)
{
    return partTwo();
}

int partOne(void)
{
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
        return 1;

    // Get size of file 
    fseek(input, 0L, SEEK_END);
    const size_t fileSize = (size_t) ftell(input);
    rewind(input);
    
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
    size_t directoryCount = 1;

    // Read input
    char *currentChar = buff;
    while (currentChar < buff + fileSize)
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
            // Move to named directory
            else 
            {
                // Check if it already exists
                if (currentDirectory->subDirectories)
                    for (size_t i = 0; 
                        i < currentDirectory->subDirectoryCount;
                        ++i)
                    {
                        if (strcmp(directoryName, currentDirectory->subDirectories[i]->name) == 0)
                        {
                            free(directoryName);
                            currentDirectory = currentDirectory->subDirectories[i];
                            goto increment;
                        }
                    }

                // Create a new directory
                Directory *directory = createDirectory(directoryName);
                appendDirectory(currentDirectory, directory);
                currentDirectory = directory;
                ++directoryCount;
            } 

            increment:
            ++currentChar;       
        }
        // ls command
        else if (*currentChar == 'l')
        {
            currentChar += 3; // goto start of file size

            do
            {
                // Get fize size
                size_t size = (size_t) atol(currentChar);
                appendFile(currentDirectory, size);
                while (*currentChar++ != '\n'); // seek start of next line
            }
            while (currentChar < buff + fileSize &&
                   *currentChar != '$');
        }
        else break; // something's wrong
    }

    // Count th total sizes of each directory
    size_t *directorySizes = malloc(directoryCount * sizeof(size_t));
    if (directorySizes == NULL)
    {
        free(buff);
        recursivelyFreeDirectory(root);
        return -2;
    }
    size_t directoriesIndexed = 0;
    getAllDirectorySizes(root, directorySizes, directoryCount, &directoriesIndexed);
    size_t answer = 0;
    for (size_t i = 0; i < directoryCount; ++i)
        if (directorySizes[i] < MAXIMUM_DIRECOTRY_SIZE)
            answer += directorySizes[i];

    printf("Your answer is: %lu\n", answer);

    free(directorySizes);
    free(buff);
    recursivelyFreeDirectory(root);
    return 0;
}

int partTwo(void)
{
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
        return 1;

    // Get size of file 
    fseek(input, 0L, SEEK_END);
    const size_t fileSize = (size_t) ftell(input);
    rewind(input);
    
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
    size_t directoryCount = 1;

    // Read input
    char *currentChar = buff;
    while (currentChar < buff + fileSize)
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
            // Move to named directory
            else 
            {
                // Check if it already exists
                if (currentDirectory->subDirectories)
                    for (size_t i = 0; 
                        i < currentDirectory->subDirectoryCount;
                        ++i)
                    {
                        if (strcmp(directoryName, currentDirectory->subDirectories[i]->name) == 0)
                        {
                            free(directoryName);
                            currentDirectory = currentDirectory->subDirectories[i];
                            goto increment;
                        }
                    }

                // Create a new directory
                Directory *directory = createDirectory(directoryName);
                appendDirectory(currentDirectory, directory);
                currentDirectory = directory;
                ++directoryCount;
            } 

            increment:
            ++currentChar;       
        }
        // ls command
        else if (*currentChar == 'l')
        {
            currentChar += 3; // goto start of file size

            do
            {
                // Get fize size
                size_t size = (size_t) atol(currentChar);
                appendFile(currentDirectory, size);
                while (*currentChar++ != '\n'); // seek start of next line
            }
            while (currentChar < buff + fileSize &&
                   *currentChar != '$');
        }
        else break; // something's wrong
    }

    // Count th total sizes of each directory
    size_t *directorySizes = malloc(directoryCount * sizeof(size_t));
    if (directorySizes == NULL)
    {
        free(buff);
        recursivelyFreeDirectory(root);
        return -2;
    }
    size_t directoriesIndexed = 0;
    getAllDirectorySizes(root, directorySizes, directoryCount, &directoriesIndexed);
    size_t usedSpace = directorySizes[0]; // root
    size_t unusedSpace = TOTAL_DISK_SPACE - usedSpace;
    printf("Used Space: %lu\n", usedSpace);
    printf("Unused Space: %lu\n", unusedSpace);
    size_t answer = TOTAL_DISK_SPACE;
    for (size_t i = 0; i < directoryCount; ++i)
    {
        if (directorySizes[i] + unusedSpace < DISK_SPACE_NEADED_FREE)
            continue;
        if (directorySizes[i] < answer)
            answer = directorySizes[i];
    }

    printf("Your answer is: %lu\n", answer);

    free(directorySizes);
    free(buff);
    recursivelyFreeDirectory(root);
    return 0;
}
