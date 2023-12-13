#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Directory
{
    char *name;
    struct Directory *parentDirectory;
    struct Directory **subDirectories;
    size_t *fileSizes;
    size_t subDirectoryCount, fileCount;
}
Directory;

Directory *createDirectory(char *directoryName);
void recursivelyFreeDirectory(Directory *directory);
bool appendDirectory(Directory *parent, Directory *child);
bool appendFile(Directory *parent, size_t fileSize);
size_t totalSize(Directory *directory);
char *substring(char *start, char *end);
void printDirectory(Directory *directory);
void getAllDirectorySizes(Directory *currentDirectory, size_t *directorySizes, size_t directoryCount, size_t *directoriesIndexed);

// Create a new directory
Directory *createDirectory(char *directoryName)
{
    Directory *directory = malloc(sizeof(Directory));
    if (directory == NULL)
        return NULL;
    directory->name = directoryName;
    directory->parentDirectory = NULL;
    directory->subDirectoryCount = 0;
    directory->subDirectories = NULL;
    directory->fileCount = 0;
    directory->fileSizes = NULL;
    return directory;
}

// Used to free root, then all child directories
void recursivelyFreeDirectory(Directory *directory)
{
    if (directory == NULL)
        return;

    free(directory->name);
    if (directory->fileSizes)
        free(directory->fileSizes);
    if (directory->subDirectories)
        for (size_t i = 0; i < directory->subDirectoryCount; ++i)
            recursivelyFreeDirectory(directory->subDirectories[i]);
    free(directory->subDirectories);
    free(directory);
}

// Create a string from another `start` through `end` (inclusive)
// Must be `free`d by user
char *substring(char *start, char *end)
{
    const size_t length = (size_t) (end - start) + 2UL;

    char *string = malloc(length * sizeof(char));
    if (string == NULL)
        return NULL;
    memcpy(string, start, length);
    string[length - 1] = 0;

    return string;
}

// Add a directory inside another
bool appendDirectory(Directory *parent, Directory *child)
{
    Directory **tmp;
    if (parent->subDirectories == NULL)
        tmp = malloc(sizeof(Directory*));
    else
        tmp = realloc(parent->subDirectories, (parent->subDirectoryCount + 1) * sizeof(Directory*));

    if (tmp == NULL)
        return false;

    child->parentDirectory = parent;
    parent->subDirectories = tmp;
    parent->subDirectories[parent->subDirectoryCount++] = child;
    return true;
}

// Add a file (size) to a directory
bool appendFile(Directory *parent, size_t fileSize)
{
    size_t *tmp;
    if (parent->fileSizes == NULL)
        tmp = malloc(sizeof(size_t));
    else
        tmp = realloc(parent->fileSizes, (parent->fileCount + 1) * sizeof(size_t*));
    
    if (tmp == NULL)
        return false;
    
    parent->fileSizes = tmp;
    parent->fileSizes[parent->fileCount++] = fileSize;
    return true;
}

// Get the size of all the file in a directory and all its subdirectories
size_t totalSize(Directory *directory)
{
    size_t sum = 0;
    if (directory->fileSizes)
        for (size_t i = 0; i < directory->fileCount; ++i)
            sum += directory->fileSizes[i];
    if (directory->subDirectories)
        for (size_t i = 0; i < directory->subDirectoryCount; ++i)
            sum += totalSize(directory->subDirectories[i]);
    return sum;    
}

// Print a directory
void printDirectory(Directory *directory)
{
    printf("Name: %s\n", directory->name);

    if (directory->subDirectories)
    {
        printf("Directories: ");
        for (size_t i = 0; i < directory->subDirectoryCount; ++i)
            printf("%s ", directory->subDirectories[i]->name);
        printf("\n");
    }

    if (directory->fileSizes)
    {    printf("Files:");
        for (size_t i = 0; i < directory->fileCount; ++i)
            printf("%lu \n", directory->fileSizes[i]);
        printf("\n");
    }

    printf("\n");
}

// Put all the sizes of all the directories into `directorySizes`
void getAllDirectorySizes
(
    Directory *currentDirectory, 
    size_t *directorySizes, 
    size_t directoryCount, 
    size_t *directoriesIndexed
)
{
    directorySizes[(*directoriesIndexed)++] = totalSize(currentDirectory);
    if (*directoriesIndexed > directoryCount - 1)
        return;
    for (size_t i = 0; i < currentDirectory->subDirectoryCount; ++i)
    {
        getAllDirectorySizes
        (
            currentDirectory->subDirectories[i],
            directorySizes,
            directoryCount,
            directoriesIndexed
        );
    }
}
