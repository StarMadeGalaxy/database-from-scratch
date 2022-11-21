/* date = October 20th 2022 8:31 pm */

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H


#include <stdlib.h>
#include <stdio.h>
#include "snake_types.h"


internal u16 get_random_number(u16 lower, u16 upper);
internal Coordinates food_generate(Map* map);
internal MapChunk* get_map_chunk(Map* map, u16 x, u16 y);
internal Map* map_alloc(u16 height, u16 width);
internal void map_init(Map* map);
internal void map_free(Map* map);

#if defined(DEBUG_MODE)
internal void spawn_food_coord(Map* map, u16 x, u16 y);
#endif // defined(DEBUG_MODE)


#endif //SNAKE_MAP_H
