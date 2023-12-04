#include "day9.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_MAX 10
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(*arr))

int partOne(void);
int partTwo(void);

int main(void)
{
    return partOne();
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
    while (fgets(buff, ARRAY_LEN(buff), input))
    {
	int direction = *buff,
	steps = atoi(buff + 2); // number starts at 3rd character
	
        // moveRope(direction, &head, &tail, pointsVisited);
    }

    freeMap(pointsVisited);
    fclose(input);
    
    return 0;
}
