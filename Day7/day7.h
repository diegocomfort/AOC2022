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

char *substring(char *start, char *end)
{
    char *string = malloc((end - start + 1) * sizeof(char));
    if (string == NULL)
        return NULL;
    memcpy(string, start, end - start);
    string[end - start] = 0;
    return string;
}

bool appendDirectory(Directory *parent, Directory *child)
{
    if (parent->subDirectories == NULL)
    {
        Directory *tmp = malloc(sizeof(Directory*));
        if (tmp == NULL)
            return false;
        parent->subDirectories = tmp;
        parent->subDirectoryCount = 1;
        parent->subDirectories[0] = child;
    }
    else
    {
        
    }
}
