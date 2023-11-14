#include <stdlib.h>
#include <stdio.h>

#define BUFF_SIZE 256
#define INPUT_PATH "input.txt"

typedef struct Directory
{
    struct Directory *parent;
    struct Directory *subDirectories;
    size_t *fileSizes;
    size_t subDirectoryCount, fileCount;
}
Directory;

Directory *createDirectory();
void appendDirectory(Directory *parent, Directory *child);
void appendFile(Directory *parent, size_t fileSize);
size_t totalSize(Directory *directory);

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
    Directory *root = NULL; //createDirectory();
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
