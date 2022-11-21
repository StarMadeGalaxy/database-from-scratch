#include "snake_map.h"


internal Coordinates food_generate(Map* map)
{
    // NOTE(Venci): -2 due to border and first index is 0
    Coordinates food_coord;
    MapChunk* food_chunk_ptr;
    
    do {
        food_coord.x = get_random_number(1, map->width - 2);
        food_coord.y = get_random_number(1, map->height - 2);
        food_chunk_ptr = get_map_chunk(map, food_coord.x, food_coord.y);
    } while (food_chunk_ptr->type != Space);
    
    food_chunk_ptr->type = Food;
    map->food_chunk = food_chunk_ptr;
    return food_coord;
}


internal u16 get_random_number(u16 lower, u16 upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}


internal MapChunk* get_map_chunk(Map* map, u16 x, u16 y)
{
    return &map->ptr[y * map->width + x];
}


internal Map* map_alloc(u16 height, u16 width)
{
    Map* game_map = (Map*)malloc(sizeof(Map));
    game_map->ptr = (MapChunk*)malloc((size_t)height * (size_t)width * sizeof(MapChunk*));
    game_map->height = height;
    game_map->width = width;
    return game_map;
}


internal void map_init(Map* map)
{
    MapChunk* chunk;
    for (u16 x = 0; x < map->width; x++)
    {
        chunk = get_map_chunk(map, x, 0);
        chunk->type = Border;
        chunk->coord.y = 0;
        chunk->coord.x = x;
    }
    
    for (u16 y = 1; y < map->height - 1; y++)
    {
        chunk = get_map_chunk(map, 0, y);
        chunk->type = Border;
        chunk->coord.x = 0;
        chunk->coord.y = y;
        
        for (u16 x = 1; x < map->width - 1; x++)
        {
            chunk = get_map_chunk(map, x, y);
            chunk->type = Space;
            chunk->coord.x = x;
            chunk->coord.y = y;
        }
        u16 last_row_x = map->width - 1;
        chunk = get_map_chunk(map, last_row_x, y);
        chunk->type = Border;
        chunk->coord.x = last_row_x;
        chunk->coord.y = y;
    }
    
    for (u16 x = 0; x < map->width; x++)
    {
        u16 last_col_y = map->height - 1;
        chunk = get_map_chunk(map, x, last_col_y);
        chunk->type = Border;
        chunk->coord.x = x;
        chunk->coord.y = last_col_y;
    }
    // NOTE(Venci): temp solution
    map->food_chunk = map->ptr;
}


internal void map_free(Map* map)
{
    free(map->ptr);
}


#if defined(DEBUG_MODE)
internal void spawn_food_coord(Map* map, u16 x, u16 y)
{
    MapChunk* food_chunk_ptr = get_map_chunk(map, x, y);
    food_chunk_ptr->type = Food;
    map->food_chunk = food_chunk_ptr;
}
#endif // defined(DEBUG_MODE)

