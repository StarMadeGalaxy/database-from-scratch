/* date = October 20th 2022 2:31 am */

#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include "snake_types.h"


internal CollisionType snake_collision_check(Snake* snake, Map* map);
internal void snake_add_speed(SnakeChunk* chunk, u16 speed);
internal void snake_grow(Snake* snake, u32 size);
internal void snake_rotate(Snake* snake);
internal void snake_free(Snake** snake);
internal void snake_move(Snake* snake);
internal Snake* snake_alloc(void);
internal void snake_init(Snake* snake, 
                         u16 start_x, 
                         u16 start_y,
                         ChunkDirection start_direction);


#endif //SNAKE_LOGIC_H
