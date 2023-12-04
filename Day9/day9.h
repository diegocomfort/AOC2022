#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int x, y;
}
Point;

typedef struct MapEntry
{
    Point key;
    int value;
    struct MapEntry *next;
}
MapEntry;

typedef struct
{
    MapEntry **entryList;
    size_t entries;
}
Map;

Map *createMap(size_t entries);
size_t hash(Point point, Map *map);
bool mapHasKey(Map *map, Point key);
bool mapPut(Map *map, Point key, int value);
bool mapGet(Map *map, Point key, int *value);
void freeMap(Map *map);

void moveRope(char direction, Point *head, Point *tail, Map *pointsVisited);
