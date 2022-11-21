#include "snake_logic.h"
// #include <stdlib.h>


internal void snake_chunk_add_speed(SnakeChunk* chunk, u16 speed)
{
    switch (chunk->direction) 
    {
        case Down: 
        {
            chunk->coord.y += speed;
            break;
        }
        case Up:
        {
            chunk->coord.y -= speed;
            break;
        }
        case Left:
        {
            chunk->coord.x -= speed;
            break;
        }
        case Right:
        {
            chunk->coord.x += speed;
            break;
        }
    }
}


internal CollisionType snake_collision_check(Snake* snake, Map* map)
{
    CollisionType result;
    for (u16 map_y = 0; map_y < map->height; map_y++)
    {
        for (u16 map_x = 0; map_x < map->width; map_x++)
        {
            MapChunk* test_chunk = get_map_chunk(map, snake->head->coord.x, snake->head->coord.y);
            switch (test_chunk->type)
            {
                case Border:
                {
                    // NOTE(Venci): I really hope that this is legal goto usage
                    // i've seen usage like that in linux kernel style guide!
                    result = BORDER_COLLISION;
                    goto collision_return;
                }
                case Food:
                {
                    result = FOOD_COLLISION;
                    goto collision_return;
                }
            }
        }
    }
    
    SnakeChunk* temp_head = snake->head;
    
    while (snake->head->next != NULL)
    {
        if (temp_head->coord.x == snake->head->next->coord.x &&
            temp_head->coord.y == snake->head->next->coord.y)
        {
            result = BODY_COLLISION;
            break;
        }
        snake->head = snake->head->next;
    }
    snake->head = temp_head;
    
    collision_return:
    return result;
}


internal void snake_move(Snake* snake)
{
    SnakeChunk* reserved_head = snake->head;
    
    while (snake->head != NULL) 
    {
        snake_chunk_add_speed(snake->head, snake->speed);
        snake->head = snake->head->next;
    }
    snake->head = reserved_head;
}


internal void snake_rotate(Snake* snake)
{
    // NOTE(Venci): Change direction at snake's corners
    // TODO(Venci): Think and simplify this code by using doubly-linked snake
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    SnakeChunk* reserved_tail = snake->tail;
    
    while (snake->tail != NULL)
    {
        if (snake->tail->prev != NULL &&
            snake->tail->direction != snake->tail->prev->direction)
        {
            snake->tail->direction = snake->tail->prev->direction;
        }
        snake->tail = snake->tail->prev;
    }
    snake->tail = reserved_tail;
#elif defined(SNAKE_SINGLY_LINKED_LIST)
    SnakeChunk* reserved_head = snake->head;
    
    u32 snake_length = 0;
    
    while (snake->head != NULL)
    {
        snake_length++;
        snake->head = snake->head->next;
    }
    snake->head = reserved_head;
    
    SnakeChunk** snake_stack = (SnakeChunk**)malloc(sizeof(SnakeChunk*) * (size_t)snake_length);
    
    u32 counter = 0;
    while (snake->head != NULL)
    {
        snake_stack[counter++] = snake->head;
        snake->head = snake->head->next;
    }
    snake->head = reserved_head;
    
    for (u32 i = snake_length - 1; i > 0; i--)
    {
        SnakeChunk* next_chunk = snake_stack[i];
        SnakeChunk* prev_chunk = snake_stack[i - 1];
        
        if (next_chunk->direction != prev_chunk->direction)
        {
            next_chunk->direction = prev_chunk->direction;
        }
    }
    free(snake_stack);
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
}


internal void snake_grow(Snake* snake, u32 size)
{
    /*
NOTE(Venci): 
size could be used for (ну что-то совсем не бонусная) bonus food, you eat it and grow by more
than 1 chunk. 
TODO(Venci):
) Have to check if there's enough space on the map
and can we generate food further
) Limit size on map size.
*/
    
    SnakeChunk* temp_head = snake->head;
    SnakeChunk* new_tail_chunk;
    
    for (u32 i = 0; i < size; i++)
    {
        new_tail_chunk = (SnakeChunk*)malloc(sizeof(SnakeChunk));
        new_tail_chunk->next = NULL;
        new_tail_chunk->type = Tail;
        
        
        if (snake->tail == NULL)
        {
            new_tail_chunk->coord = snake->head->coord;
        }
        else
        {
            new_tail_chunk->coord = snake->tail->coord;
        }
        
        new_tail_chunk->direction = snake->head->direction;
        
        switch (snake->head->direction)
        {
            case Down:
            {
                new_tail_chunk->coord.y--;
                break;
            }
            case Up:
            {
                new_tail_chunk->coord.y++;
                break;
            }
            case Left:
            {
                new_tail_chunk->coord.x++;
                break;
            }
            case Right:
            {
                new_tail_chunk->coord.x--;
                break;
            }
        }
        
        while (snake->head->next != NULL)
        {
            snake->head = snake->head->next;
        }
        
#if defined(SNAKE_DOUBLY_LINKED_LIST)
        new_tail_chunk->prev = snake->head;
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
        
        snake->head->next = new_tail_chunk;
        snake->tail = new_tail_chunk;
        
        if (snake->head->type != Head)
        {
            snake->head->type = Body;
        }
        snake->head = temp_head;
    }
}




internal void snake_init(Snake* snake, 
                         u16 start_x, 
                         u16 start_y, 
                         ChunkDirection start_direction)
{
    snake->head->direction = start_direction;
    snake->head->coord.x = start_x;
    snake->head->coord.y = start_y;
    snake->head->next = NULL;
    snake->head->type = Head;
    snake->state = Alive;
    snake->speed = 1;
    snake->tail = NULL;
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    snake->head->prev = NULL;
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
}


internal Snake* snake_alloc(void)
{
    Snake* new_snake = (Snake*)malloc(sizeof(Snake));
    new_snake->head = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    return new_snake;
}


internal void snake_free(Snake** snake)
{
    SnakeChunk* temp_head;
    Snake* snake_pointer = *snake;
    
    while (snake_pointer->head != NULL)
    {
        temp_head = snake_pointer->head->next;
        free(snake_pointer->head);
        snake_pointer->head = temp_head;
    }
    free(snake_pointer);
    *snake = NULL;
}


