#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFF_SIZE 15
#define WIDTH 40
#define HEIGHT 6

int partOne(void);
int partTwo(void);
void endOfCyclePartOne(int *cycles, int *X, int *strengthSum);
void endOfCyclePartTwo(int *cycles, int *X, int *strengthSum, char CRT[HEIGHT][WIDTH]);

int main(void)
{
    return partTwo();
}

int partOne(void)
{
    int X = 1, cycles = 0, strengthSum = 0;
    char buff[BUFF_SIZE];

    FILE *input = fopen("input.txt", "r");
    if (!input)
	return 1;

    while (fgets(buff, BUFF_SIZE, input))
    {
	char *currentChar = buff;
	switch (*currentChar)
	{
	case 'a': // addx
	    while (currentChar < buff + 10 &&
		   (*currentChar++) != ' '); /* Goto start of V (input number) */
	    int V = atoi(currentChar);
	    ++cycles;
	    endOfCyclePartOne(&cycles, &X, &strengthSum);
	    /* X += V; */
	    ++cycles;
	    endOfCyclePartOne(&cycles, &X, &strengthSum);
	    X += V;
	    break;
	case 'n': // noop
	    ++cycles;
	    endOfCyclePartOne(&cycles, &X, &strengthSum);
	    break;
	}
    }

    printf("Signal Strenght Sum: %i\n", strengthSum);

    return 0;
}

void endOfCyclePartOne(int *cycles, int *X, int *strengthSum)
{
    if (*cycles > 0 && (*cycles - 20) % 40 == 0)
    {
	*strengthSum += (*cycles) * (*X);
    }
}

int partTwo(void)
{
    int X = 1, cycles = 0, strengthSum = 0;
    char buff[BUFF_SIZE],
	 CRT[HEIGHT][WIDTH];
    
    FILE *input = fopen("input.txt", "r");
    if (!input)
	return 1;

    while (fgets(buff, BUFF_SIZE, input))
    {
	char *currentChar = buff;
	switch (*currentChar)
	{
	case 'a': // addx
	    while (currentChar < buff + 10 &&
		   (*currentChar++) != ' '); /* Goto start of V (input number) */
	    int V = atoi(currentChar);
	    endOfCyclePartTwo(&cycles, &X, &strengthSum, CRT);
	    ++cycles;
	    endOfCyclePartTwo(&cycles, &X, &strengthSum, CRT);
	    ++cycles;
	    X += V;
	    break;
	case 'n': // noop
	    endOfCyclePartTwo(&cycles, &X, &strengthSum, CRT);
	    ++cycles;
	    break;
	}
    }

    for (int y = 0; y < HEIGHT; ++y)
    {
	for (int x = 0; x < WIDTH; ++x)
	{
	    putchar(CRT[y][x] ? CRT[y][x] : '.');
	}
	putchar('\n');
    }
		    

    return 0;
}

void endOfCyclePartTwo(int *cycles, int *X, int *strengthSum, char CRT[HEIGHT][WIDTH])
{
    int CRTy = *cycles / WIDTH,
	CRTx = *cycles % WIDTH,
	spriteX = *X;
    for (int i = -1; i <= 1; ++i)
    {
	if (spriteX + i == CRTx)
	{
	    CRT[CRTy][spriteX + i] = '#';
	    return;
	}
    }
	
}
