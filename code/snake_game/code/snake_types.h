/* date = October 20th 2022 2:05 am */

#ifndef SNAKE_TYPES_H
#define SNAKE_TYPES_H

#include "base_types.h"


typedef enum ChunkDirection
{
    None, Up, Left, Down, Right
} ChunkDirection;


typedef enum ChunkType
{
    Tail, Head, Body, Food, Border, Space
} ChunkType;


typedef enum SnakeState
{
    Alive, Dead
} SnakeState;


typedef enum CollisionType
{
    NONE_COLLISION, BORDER_COLLISION, BODY_COLLISION, FOOD_COLLISION
} CollisionType;


/* TODO(Venci): Implement key-value data structure to store chunk symbol there */
#if !defined(GUI_ENABLED)
# define HEAD_CHAR '@'
# define BODY_CHAR 'o'
# define TAIL_CHAR '*'

# define BORDER_CHAR '#'
# define FOOD_CHAR '$'
# define SPACE_CHAR ' '
#endif // defined(GUI_ENABLED)


typedef struct Coordinates
{
    u16 x;
    u16 y;
} Coordinates;


typedef struct SnakeChunk
{
    ChunkDirection direction;
    ChunkType type;
    struct SnakeChunk* next;
    Coordinates coord;
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    struct SnakeChunk* prev;
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
} SnakeChunk;


typedef struct MapChunk
{
    ChunkType type;
    Coordinates coord;
} MapChunk;


typedef struct Snake
{
    SnakeChunk* head;
    SnakeChunk* tail;
    SnakeState state;
    u16 speed;
} Snake;


typedef struct Map
{
    u16 height;
    u16 width;
    MapChunk* ptr;
    // NOTE(Venci): temp solution
    MapChunk* food_chunk;
} Map;


#endif /* SNAKE_TYPES_H */
