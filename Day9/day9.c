#include "day9.h"
#include <stdio.h>

#define ABS(x) (((x) > 0) ? (x) : -(x)) 
#define SGN(x) (((x) == 0) ? 0 : (((x) > 0) ? 1 : -1))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void freeEntryList (MapEntry *entry);

Map *createMap(size_t entries)
{
    if (entries == 0)
	return NULL;

    Map *map = malloc(sizeof(Map));
    if (!map)
	return NULL;

    map->entryList = calloc(entries, sizeof(MapEntry*));
    if (!map->entryList)
    {
	free(map);
	return NULL;
    }

    map->entries = entries;
    return map;
}

size_t hash(Point point, Map *map)
{
    return (size_t) (point.y + 31 * point.x) % map->entries;
}

bool mapHasKey(Map *map, Point point)
{
    if (map == NULL || map->entryList == NULL || map->entries == 0)
	return false;
    for (MapEntry *entry = map->entryList[hash(point, map)];
	 entry != NULL; entry = entry->next)
    {
        if (entry->key.x == point.x && entry->key.y == point.y)
	    return true;
    }
    return false;
}

bool mapPut(Map *map, Point key, int value)
{
    if (map == NULL || map->entryList == NULL || map->entries == 0)
	return false;
    size_t hashCode = hash(key, map);
    for (MapEntry *entry = map->entryList[hashCode];
        entry; entry = entry->next)
    {
	if (entry->key.x == key.x && entry->key.y == key.y)
	{
	    entry->value = value;
	    return true;
        }
    }
    MapEntry *newEntry = malloc(sizeof(MapEntry));
    if (!newEntry)
	return false;
    newEntry->key = key;
    newEntry->value = value;
    MapEntry *previousEntry = map->entryList[hashCode];
    map->entryList[hashCode] = newEntry;
    map->entryList[hashCode]->next = previousEntry;
    return true;
}

bool mapGet(Map *map, Point key, int *value)
{
    if (map == NULL || map->entryList == NULL || map->entries == 0)
	return false;
    for (MapEntry *entry = map->entryList[hash(key, map)];
	 entry != NULL; entry = entry->next)
    {
        if (entry->key.x == key.x && entry->key.y == key.y)
	{
	    *value = entry->value;
	    return true;
	}
    }
    return false;
}    

void freeMap(Map *map)
{
    if (map == NULL || map->entryList == NULL || map->entries == 0)
	return;
    for (size_t i = 0; i < map->entries; ++i)
	freeEntryList(map->entryList[i]);
    free(map->entryList);
    free(map);
}

void freeEntryList(MapEntry *entry)
{
    if (!entry)
	return;
    if (entry->next)
	freeEntryList(entry->next);
    free(entry);
}

void printMapEntries(Map *map)
{
    for (int i = 0; i < map->entries; ++i)
    {
	if (!map->entryList[i])
	    continue;
	for (MapEntry *entry = map->entryList[i]; entry; entry = entry->next)
	{
	    printf("Key: {%i, %i} -> Value: %i\n", entry->key.x, entry->key.y, entry->value);
	}
    }

}

void followHead(Point *head, Point *tail)
{
    int dx = head->x - tail->x,
        dy = head->y - tail->y;
    if (ABS(dx) > 1 || ABS(dy) > 1)
    {
	tail->x += SGN(dx);
	tail->y += SGN(dy);
    }
    else if (ABS(dx) > 1)
	tail->x += SGN(dx);
    else if (ABS(dy) > 1)
	tail->y += SGN(dy);

    // Prints it
    /* for (int y = 4; y >= 0; --y) */
    /* { */
    /* 	for (int x = 0; x < 6; ++x) */
    /* 	{ */
    /* 	    char c = '.'; */
    /* 	    if (x == tail->x && y == -tail->y) */
    /* 		c = 'T'; */
    /* 	    if (x == head->x && y == -head->y) */
    /* 		c = 'H'; */
    /* 	    putchar(c); */
    /* 	} */
    /* 	putchar('\n'); */
    /* } */
    /* putchar('\n'); */
}
	

void moveRope(char direction, int steps, Point *head, Point *tail, Map *pointsVisited)
{
    // TODO
    for (int i = 0; i < steps; ++i)
    {
	switch (direction)
	{
	case 'U':
	    --head->y;
	    break;
	case 'D':
	    ++head->y;
	    break;
	case 'L':
	    --head->x;
	    break;
	case 'R':
	    ++head->x;
	    break;
	}
	followHead(head, tail);
	mapPut(pointsVisited, *tail, 1);
    }
}

void moveBigRope(char direction, int steps, Point knots[10], Map *pointsVisited)
{
    for (int i = 0; i < steps; ++i)
    {
	switch (direction)
	{
	case 'U':
	    --knots[0].y;
	    break;
	case 'D':
	    ++knots[0].y;
	    break;
	case 'L':
	    --knots[0].x;
	    break;
	case 'R':
	    ++knots[0].x;
	    break;
	}

	for (int i = 0; i < 9; ++i)
	    followHead(knots + i, knots + i + 1);
	mapPut(pointsVisited, knots[9], 1);
    }
}
