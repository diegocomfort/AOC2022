#include "day9.h"

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
	    return false;
    }
    return false;
}

bool mapPut(Map *map, Point key, int value)
{
    if (map == NULL || map->entryList == NULL || map->entries == 0)
	return false;
    MapEntry *newEntry = malloc(sizeof(MapEntry));
    if (!newEntry)
	return false;
    newEntry->key = key;
    newEntry->value = value;
    size_t hashCode = hash(key, map);
    MapEntry *previousEntry = map->entryList[hashCode];
    map->entryList[hashCode] = newEntry;
    map->entryList[hashCode]->next = previousEntry;
    return true;
}

bool mapGet(Map *map, Point key, int *value)
{
    // TODO
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
    free(map);
}

void freeEntryList (MapEntry *entry)
{
    if (!entry)
	return;
    if (entry->next)
	freeEntryList(entry->next);
    free(entry);
}

void moveRope(char direction, Point *head, Point *tail, Map *pointsVisited)
{
    // TODO
    switch (direction)
    {
    case 'U':
	break;
    case 'D':
        break;
    case 'L':
        break;
    case 'R':
        break;
    }
}
