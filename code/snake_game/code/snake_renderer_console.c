#include "snake_renderer_console.h"

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#endif /*_WIN32*/


#if defined(_WIN32)
#   define FILE_DESCRIPTOR HANDLE
#else 
#   define FILE_DESCRIPTOR int
#endif // defined(_WIN32)


typedef struct ConsoleRenderer
{
    ConsoleRendererCommand commands;
    ConsoleSize size; 
    void* frame_data;
    FILE_DESCRIPTOR console_handler;
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO renderer_cbsi;
#elif defined(__linux__)
    int console_handler;
#endif // defined(_WIN32)    
} ConsoleRenderer;


SRC_API u16 console_is_key_pressed(u32 virtual_key_code)
{
#if defined(_WIN32)
    return (GetAsyncKeyState(virtual_key_code) & MSB(u16));
#endif
}


SRC_API void console_renderer_destroy(ConsoleRenderer* renderer)
{
    free(renderer->frame_data);
    free(renderer);
}


SRC_API void console_cursor_hide(ConsoleRenderer* renderer)
{
#if defined(_WIN32)
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
#endif // defined(_WIN32)
}


SRC_API ConsoleRenderer* console_renderer_create(u16 screen_height,
                                                 u16 screen_width)
{
    ConsoleRenderer* renderer = (ConsoleRenderer*)malloc(sizeof(ConsoleRenderer));
    
    size_t data_size = (size_t)screen_height * (size_t)screen_width;
    
    renderer->frame_data = (CONSOLE_FRAME_TYPE*)malloc(data_size * sizeof(CONSOLE_FRAME_TYPE));
    renderer->size.height = screen_height;
    renderer->size.width = screen_width;
#if defined(_WIN32) 
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor_hide(renderer);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(renderer->console_handler, &cbsi);
    renderer->renderer_cbsi = cbsi;
    renderer->renderer_cbsi.dwCursorPosition.X = 0;
    renderer->renderer_cbsi.dwCursorPosition.Y += 1;
#endif // defined(_WIN_32)
    return renderer;
}


#define MAKE_MAP
#define MAKE_SNAKE
SRC_API void console_make_frame(ConsoleRenderer* renderer, 
                                Snake* snake, 
                                Map* game_map)
{
    // NOTE(Venci): filling renderer data with map
    for (u16 y = 0; y < game_map->height; y++) 
    {
        for (u16 x = 0; x < game_map->width; x++) 
        {
            u32 index = y * renderer->size.width + x;
            switch(get_map_chunk(game_map, x, y)->type) 
            {
                case Space:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = SPACE_CHAR;
                    break;
                }
                case Food:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = FOOD_CHAR;
                    break;
                }
                case Border:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BORDER_CHAR;
                    break;
                }
            }
        }
    }
    
    // NOTE(Venci): filling renderer data with snake
    SnakeChunk* temp_chunk = snake->head;
    while (snake->head != NULL)
    {
        u32 index = snake->head->coord.y * renderer->size.width + snake->head->coord.x;
        switch (snake->head->type)
        {
            
            case Body:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BODY_CHAR;
                break;
            }
            case Head:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = HEAD_CHAR;
                break;
            }
            case Tail:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = TAIL_CHAR;
                break;
            }
        }
        snake->head = snake->head->next;
    }
    snake->head = temp_chunk;
}


SRC_API void console_cursor_begin_move(ConsoleRenderer* renderer)
{
#if defined(_WIN32)
    SetConsoleCursorPosition(renderer->console_handler,
                             renderer->renderer_cbsi.dwCursorPosition);
#endif // defined(_WIN32)
}


SRC_API void console_render_frame(ConsoleRenderer* renderer)
{
    for (u16 y = 0; y < renderer->size.height; y++)
    {
        for (u16 x = 0; x < renderer->size.width; x++)
        {
            u32 index = y * renderer->size.width + x;
            fputc(((char*)renderer->frame_data)[index], stdout);
        }
        fputc('\n', stdout);
    }
} 
