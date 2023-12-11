#include "day9.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_MAX 10

int partOne(void);
int partTwo(void);

int main(void)
{
    return partTwo();
}

int partOne(void)
{
    FILE *input = fopen("input.txt", "r");
    if (!input)
    {
	fprintf(stderr, "couldn't open input");
	return 1;
    }

    char buff[LINE_MAX] = {0};
    Point head = {.x = 0, .y = 0},
	  tail = {.x = 0, .y = 0};
    Map *pointsVisited = createMap(200);
    while (fgets(buff, LINE_MAX, input))
    {
	int direction = *buff,
	    steps = atoi(buff + 2); // number starts at 3rd character
        moveRope(direction, steps, &head, &tail, pointsVisited);
    }

    int count = 0;
    for (int i = 0; i < pointsVisited->entries; ++i)
    {
	for (MapEntry *entry = pointsVisited->entryList[i];
	     entry; entry = entry->next)
	{
	    ++count;
	}
    }

    printf("The tail visited %i different tiles\n", count);
    
    freeMap(pointsVisited);
    fclose(input);
    
    return 0;
}

int partTwo(void)
{
    FILE *input = fopen("input.txt", "r");
    if (!input)
    {
	fprintf(stderr, "couldn't open input");
	return 1;
    }

    char buff[LINE_MAX] = {0};
    Point knots[10] = {0};
    Map *pointsVisited = createMap(200);
    while (fgets(buff, LINE_MAX, input))
    {
	int direction = *buff,
	    steps = atoi(buff + 2); // number starts at 3rd character
        moveBigRope(direction, steps, knots, pointsVisited);
    }

    int count = 0;
    for (int i = 0; i < pointsVisited->entries; ++i)
    {
	for (MapEntry *entry = pointsVisited->entryList[i];
	     entry; entry = entry->next)
	{
	    ++count;
	}
    }

    printf("The tail visited %i different tiles\n", count);
    
    freeMap(pointsVisited);
    fclose(input);
    
    return 0;
}
