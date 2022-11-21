// NOTE(Venci): this entire file should GUI_ENABLED independent 
// NOTE(Venci): and platform independent as well

#include "snake_game.h"
#include <time.h>


internal void snake_game_start()
{
    srand((u32)time(NULL)); 
    
    const u16 screen_width = 25;
    const u16 screen_height = 15;
    
    Map* game_map = map_alloc(screen_height, screen_width);
    map_init(game_map);
    
    Snake* snake = snake_alloc();
    snake_init(snake, (u16)(screen_width / 2), (u16)(screen_height / 2), None);
    
    GameInput game_input;
    
#if !defined(GUI_ENABLED)
    ConsoleRenderer* renderer = console_renderer_create(screen_height, screen_width);
#elif defined(GUI_ENABLED)
#endif // defined(GUI_ENABLED)
    while (snake->state == Alive)
    {
#if !defined(GUI_ENABLED)
        if (console_is_key_pressed((u32)VK_W))
        {
            game_input.keyboard_keys[KEYBOARD_W] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_A))
        {
            game_input.keyboard_keys[KEYBOARD_A] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_S))
        {
            game_input.keyboard_keys[KEYBOARD_S] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_D))
        {
            game_input.keyboard_keys[KEYBOARD_D] = BUTTON_UP;
        }
#if defined(DEBUG_MODE)
        if (console_is_key_pressed((u32)VK_SPACE))
        {
            game_input.keyboard_keys[KEYBOARD_SPACE] = BUTTON_UP;
        }
#endif // defined(DEBUG_MODE)
        if (console_is_key_pressed((u32)VK_ESCAPE))
        {
            break;
        }
        
        if (!console_is_key_pressed((u32)VK_W))
        {
            game_input.keyboard_keys[KEYBOARD_W] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_A))
        {
            game_input.keyboard_keys[KEYBOARD_A] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_S))
        {
            game_input.keyboard_keys[KEYBOARD_S] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_D))
        {
            game_input.keyboard_keys[KEYBOARD_D] = BUTTON_DOWN;
        }
#if defined(DEBUG_MODE)
        if (!console_is_key_pressed((u32)VK_SPACE))
        {
            game_input.keyboard_keys[KEYBOARD_SPACE] = BUTTON_DOWN;
        }
#endif // defined(DEBUG_MODE)
        
        game_render_update(&game_input, snake, game_map, renderer);
        
#endif /* !defined(GUI_ENABLED)*/
        Sleep(50);
    }
    //system("PAUSE");
    
#if defined(GUI_ENABLED)
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);               
    while (!WindowShouldClose())    
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        CloseWindow();       
    }
#endif // defined(GUI_ENABLED)
#if defined(DEBUG_MODE)
    if (snake == NULL)
        puts("Snake has been NULLed");
#endif // defined(DEBUG_MODE)
    map_free(game_map);
    snake_free(&snake);
    console_renderer_destroy(renderer);
}