#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define OP_OLD -1
#define DA_CAP_INC 25

/* Dynamic Array  */
struct da
{
    int *items;
    size_t cap, size;
};

struct monkey
{
    struct da items;
    int op_l, op_r; // operation left, right parameters (-1 = old)
    char op;
    int div_test;
    int true_throw, false_throw;
};

int monkey_apply_op(struct monkey *monkey); // TODO

bool da_init(struct da *da, size_t cap)
{
    if (da == NULL || cap == 0 || da->items != NULL)
	return false;
    da->items = malloc(cap * sizeof(int));
    if (da->items == NULL)
	return false;
    memset(da->items, 0, sizeof(int) * cap);
    da->cap = cap;
    da->size = 0;
    return true;
}

void da_terminate(struct da *da)
{
    if (da == NULL)
	return;
    if (da->items != NULL)
	free(da->items);
    da->items = NULL;
    da->cap = da->size = 0;
    return;
}

bool da_push(struct da *da, int item)
{
    if (da == NULL)
	return false;
    if (da->items == NULL)
	if (!da_init(da, DA_CAP_INC))
	    return false;
    if (da->size == da->cap)
    {
	int *tmp = realloc(da->items, (da->cap + DA_CAP_INC) * sizeof(int));
	if (!tmp)
	    return false;
	da->items = tmp;
	da->cap += DA_CAP_INC;
	memset(da->items + da->size, 0, sizeof(int) * DA_CAP_INC);
    }
    da->items[da->size++] = item;
    return true;
}

bool da_parse_and_push(struct da *da, char *items)
{
    if (da == NULL)
	return false;

    char *start = items, *end = NULL;
    int n;

    while (*start != '\0')
    {
	n = (int) strtol(start, &end, 10);
	if (!da_push(da, n))
	    return false;
	if (start == end || *end == '\0')
	    break;
	start = end + 1;
	end = NULL;
    }
    
    return true;
}

int da_peek(struct da *da)
{
    if (!da || da->items == NULL || da->size < 0)
	return 0;
    return da->items[da->size - 1];
}

int da_pop(struct da *da)
{
    if (!da || da->items == NULL || da->size < 0)
	return 0;
    int res = da->items[da->size - 1];
    da->items[da->size - 1] = 0;
    return res;
}

void da_print(struct da *da)
{
    if (da == NULL || da->items == NULL)
	return;
    printf("{");
    for (size_t i = 0; i < da->size; ++i)
	printf("%s%d", ((i == 0) ? "" : ", "), da->items[i]);
    printf("}\n");
}
