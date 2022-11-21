/* date = November 2nd 2022 2:31 pm */


#include "snake_game_platform.h"
#include "base_types.h"
#include "snake_logic.h"


internal void game_render_update(GameInput* input,
                                 Snake* snake,
                                 Map* game_map,
                                 CURRENT_RENDERER* renderer)
{
#if defined(DEBUG_MODE)
    if (input->keyboard_keys[KEYBOARD_SPACE])
    {
        snake->head->direction = None;
    }
#endif // defined(DEBUG)
    if (input->keyboard_keys[KEYBOARD_W] && 
        snake->head->direction != Down) 
    {
        snake->head->direction = Up;
    }
    if (input->keyboard_keys[KEYBOARD_A] && 
        snake->head->direction != Right)
    {
        snake->head->direction = Left;
    }
    if (input->keyboard_keys[KEYBOARD_S] && 
        snake->head->direction != Up)
    {
        snake->head->direction = Down;
    }
    if (input->keyboard_keys[KEYBOARD_D] && 
        snake->head->direction != Left)
    {
        snake->head->direction = Right;
    }
    if (snake->head->direction != None)
    {
        snake_move(snake);
        snake_rotate(snake);
    }
    
    CollisionType snake_collision = snake_collision_check(snake, game_map);
    
    switch (snake_collision)
    {
        case BORDER_COLLISION:
        {
            snake->state = Dead;
            break;
        }
        case BODY_COLLISION:
        {
            snake->state = Dead;
            break;
        }
        case FOOD_COLLISION:
        {
            game_map->food_chunk->type = Space;
            snake_grow(snake, 1);
            break;
        }
    }
    
    // NOTE(Venci): temp solution
    
    if (game_map->food_chunk->type != Food)
        food_generate(game_map);
    
    
#if !defined(GUI_ENABLED)
    console_cursor_begin_move(renderer);
    console_make_frame(renderer, snake, game_map);
    console_render_frame(renderer);
#endif // !defined(GUI_ENABLED)
    
#if defined(DEBUG_MODE)
    local int test_var;
    
    if (test_var >= 100) test_var = 0;
    
    // W
    if (input->keyboard_keys[KEYBOARD_W] == BUTTON_UP)
        fprintf(stdout, "W key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_W] == BUTTON_DOWN)
        fprintf(stdout, "W key is unpressed %d               \n", test_var);
    
    // A
    if (input->keyboard_keys[KEYBOARD_A] == BUTTON_UP)
        fprintf(stdout, "A key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_A] == BUTTON_DOWN)
        fprintf(stdout, "A key is unpressed %d               \n", test_var);
    
    // S
    if (input->keyboard_keys[KEYBOARD_S] == BUTTON_UP)
        fprintf(stdout, "S key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_S] == BUTTON_DOWN)
        fprintf(stdout, "S key is unpressed %d               \n", test_var);
    
    // D
    if (input->keyboard_keys[KEYBOARD_D] == BUTTON_UP)
        fprintf(stdout, "D key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_D] == BUTTON_DOWN)
        fprintf(stdout, "D key is unpressed %d               \n", test_var);
    
    // SPACE
    if (input->keyboard_keys[KEYBOARD_SPACE] == BUTTON_UP)
        fprintf(stdout, "Space key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_SPACE] == BUTTON_DOWN)
        fprintf(stdout, "Space key is unpressed %d               \n", test_var);
    
    fprintf(stdout, "snake->tail      : %p\n", snake->tail);
    fprintf(stdout, "snake->head      : %p\n", snake->head);
    fprintf(stdout, "snake->head->next: %p\n", snake->head->next);
    fprintf(stdout, "snake->head->type: %d\n", snake->head->type);
    fprintf(stdout, "Snake->head->x   : %d\n", snake->head->coord.x);
    fprintf(stdout, "snake->head->y   : %d\n", snake->head->coord.y);
    fprintf(stdout, "snake->head->dn  : %d\n", snake->head->direction);
    fprintf(stdout, "random test 1-5  : %d\n", get_random_number(1, 5));
    fprintf(stdout, "Game mode: DEBUG_MODE\n");
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    fprintf(stdout, "Snake structure: DOUBLY_LINKED_LIST\n");
#elif defined(SNAKE_SINGLY_LINKED_LIST)
    fprintf(stdout, "Snake structure: SINGLY_LINKED_LIST\n");
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
    
    test_var++;
#endif // defined(DEBUG_MODE) 
}