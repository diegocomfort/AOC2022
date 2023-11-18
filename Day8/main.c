#include "day8.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_FILE  "input.txt"
#define WIDTH       99UL
#define HEIGHT      99UL

int partOne(void);
int partTwo(void);

int main(void)
{
    return partOne();
}

int partOne(void)
{
    char buff[HEIGHT][WIDTH];
    bool visible[HEIGHT][WIDTH] = {0};

    FILE *input = fopen(INPUT_FILE, "r");
    if (!input) return 1;
    for (size_t y = 0; y < HEIGHT; ++y)
    {
        fread(buff[y], sizeof(char), WIDTH, input);
        fgetc(input); // skip newline
    }   

    size_t visibleTrees = 2 * (HEIGHT + WIDTH) - 4;
    printf("Visible trees: %lu\n", visibleTrees);
    char max;

    // Top -> Bottom
    for (size_t x = 1; x < WIDTH - 1; ++x)
    {
        max = buff[0][x];
        for (size_t y = 1; y < HEIGHT - 1; ++y)
        {
            if (max == 9) break;
            if (buff[y][x] > max)
            {
                max = buff[y][x];
                if (!visible[y][x])
                {
                    ++visibleTrees;
                    visible[y][x] = true;
                }
            }
        }
    }

    // Bottom -> Top
    for (size_t x = 1; x < WIDTH - 1; ++x)
    {
        max = buff[HEIGHT - 1][x];
        for (size_t y = HEIGHT - 2; y > 0; --y)
        {
            if (max == 9) break;
            if (buff[y][x] > max)
            {
                max = buff[y][x];
                if (!visible[y][x])
                {
                    ++visibleTrees;
                    visible[y][x] = true;
                }
            }
        }
    }

    // Left -> Right
    for (size_t y = 1; y < HEIGHT - 1; ++y)
    {
        max = buff[y][0];
        for (size_t x = 1; x < WIDTH - 1; ++x)
        {
            if (buff[y][x] > max)
            {
                max = buff[y][x];
                if (!visible[y][x])
                {
                    ++visibleTrees;
                    visible[y][x] = true;
                }
            }
        }
    }

    // Right -> Left
    for (size_t y = 1; y < HEIGHT - 1; ++y)
    {
        max = buff[y][WIDTH - 1];
        for (size_t x = WIDTH - 2; x > 0; --x)
        {
            if (buff[y][x] > max)
            {
                max = buff[y][x];
                if (!visible[y][x])
                {
                    ++visibleTrees;
                    visible[y][x] = true;
                }
            }
        }
    }

    printf("Answer: %lu\n", visibleTrees);

    return 0;
}

int partTwo(void)
{
    char buff[HEIGHT][WIDTH];
    bool visible[HEIGHT][WIDTH] = {0};
    size_t scenicScores[HEIGHT][WIDTH];

    FILE *input = fopen(INPUT_FILE, "r");
    if (!input) return 1;
    for (size_t y = 0; y < HEIGHT; ++y)
    {
        fread(buff[y], sizeof(char), WIDTH, input);
        fgetc(input); // skip newline

        for (size_t x = 0; x < WIDTH; ++x)
            scenicScores[y][x] = 1UL;
    }   

    size_t visibleTrees = 2 * (HEIGHT + WIDTH) - 4;
    printf("Visible trees: %lu\n", visibleTrees);
    size_t directionalScore;

    // Top -> Bottom
    for (size_t x = 1; x < WIDTH - 1; ++x)
    {
        directionalScore = 1UL;
        for (size_t y = 1; y < HEIGHT - 1; ++y)
        {
            
        }
    }

    // Bottom -> Top
    for (size_t x = 1; x < WIDTH - 1; ++x)
    {
        for (size_t y = HEIGHT - 2; y > 0; --y)
        {
            
        }
    }

    // Left -> Right
    for (size_t y = 1; y < HEIGHT - 1; ++y)
    {
        for (size_t x = 1; x < WIDTH - 1; ++x)
        {
            
        }
    }

    // Right -> Left
    for (size_t y = 1; y < HEIGHT - 1; ++y)
    {
        for (size_t x = WIDTH - 2; x > 0; --x)
        {
            
        }
    }

    size_t maxScenicScore = 0;

    printf("Answer: %lu\n", maxScenicScore);

    return 0;
}

