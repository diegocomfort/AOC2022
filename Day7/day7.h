#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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
    free(directory->name);
    if (directory->fileSizes)
        free(directory->fileSizes);
    if (directory->subDirectories)
        for (int i = 0; i < directory->subDirectoryCount; ++i)
            recursivelyFreeDirectory(&directory->subDirectories[i]);
    free(directory);
}

// Create a string from another
char *substring(char *start, char *end)
{
    char *string = malloc((end - start + 1) * sizeof(char));
    if (string == NULL)
        return NULL;
    memcpy(string, start, end - start);
    string[end - start] = 0;
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
    // TODO:
}