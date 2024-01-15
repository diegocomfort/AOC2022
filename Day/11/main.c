#include "day11.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_MONKEYS 4
#define BUFF_SIZE 256

int partOne(void);
int partTwo(void);

int main(void)
{
    return partOne();
}

int partOne(void)
{
    struct monkey monkeys[NUM_MONKEYS] = {0};
    char buff[BUFF_SIZE];
    int m_i;
    char m_op_l[6] = {0};
    char m_op_r[6] = {0};
    char m_items[256] = {0};
	
    FILE *input;

    input = fopen("input.txt", "r");

    while (fgets(buff, sizeof(buff), input))
    {
        // Monkey number line
	sscanf(buff, "Monkey %d:\n", &m_i);
	memset(buff, 0, sizeof(buff));

	// Items line
	fgets(buff, sizeof(buff), input);
	sscanf(buff, "  Starting items: %255[^\n]\n", &m_items);
	memset(buff, 0, sizeof(buff));

	// Operation line
	fgets(buff, sizeof(buff), input);
	sscanf(buff, "  Operation: new = %s %c %s\n", &m_op_l,
	       &monkeys[m_i].op,
	       &m_op_r);
	memset(buff, 0, sizeof(buff));

	// Divisible line
	fgets(buff, sizeof(buff), input);
	sscanf(buff, "  Test: divisible by %d\n", &monkeys[m_i].div_test);
	memset(buff, 0, sizeof(buff));

	// True throw line
	fgets(buff, sizeof(buff), input);
	sscanf(buff, "    If true: throw to monkey %d\n", &monkeys[m_i].true_throw);
	memset(buff, 0, sizeof(buff));

	// False throw line
	fgets(buff, sizeof(buff), input);
	sscanf(buff, "    If false: throw to monkey %d\n", &monkeys[m_i].false_throw);

        // Read blank line
	fgets(buff, sizeof(buff), input);
	memset(buff, 0, sizeof(buff));
	
	// Parse operation
	if (m_op_l[0] == 'o')
	    monkeys[m_i].op_l = OP_OLD;
	else
	    monkeys[m_i].op_l = atoi(m_op_l);
	if (m_op_r[0] == 'o')
	    monkeys[m_i].op_r = OP_OLD;
	else
	    monkeys[m_i].op_r = atoi(m_op_r);
	
	// Parse items
	da_parse_and_push(&monkeys[m_i].items, m_items);

	memset(m_items, 0, sizeof(m_items));
	memset(m_op_l, 0, sizeof(m_op_l));
	memset(m_op_r, 0, sizeof(m_op_r));
    }
    
    fclose(input);
    for (int i = 0; i < NUM_MONKEYS; ++i)
	da_terminate(&monkeys[i].items);
    return 0;
}

int operation(int left, char operator, int right)
{
    switch (operator)
    {
    case '+':
	return left + right;
    case '-':
	return left - right;
    case '*':
	return left * right;
    case '/':
	return left / right;
    default:
	return 0;
    }
}
