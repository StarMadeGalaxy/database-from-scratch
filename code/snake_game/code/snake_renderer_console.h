/* date = October 20th 2022 2:27 am */

#ifndef SNAKE_RENDERER_CONSOLE
#define SNAKE_RENDERER_CONSOLE

#ifdef _WIN32
#include <Windows.h>
#endif /*_WIN32*/

#include <stdlib.h>
#include <conio.h>

#include "snake_map.c"
#include "snake_game_platform.h"

/* NOTE(Venci): There's probably another way without including snake_map.h.
Im wondering how could it be implemented in more effective 
and concise way. e.g. pushcommand, virual machine idk... 
Maybe my thoughts are completely wrong, but anyway i'm a bit 
frustrated thinking about that so far. We will see in the future */

// TODO(Venci): build renderer as dll in learning purposes
#define SRC_API __declspec(dllexport)

/* NOTE(Venci): 
I'm having a problem with designig this piece of code.
1) Im not sure what is the best practice to separate input layer
2) Im not sure how shouil implement renderer structure (C struct)
3) Where should I have the main loop?
4) And finally, should i even think about that for now, or I just should
keep working on the project without thinking about the design so hard???
Because it's definitely not the last project in my entire life. */


// NOTE(Venci): WHY DOES ENABLING UNICODE_ENABLED BREAK EVERYTHING???
// NOTE(Venci): There's something i clearly do not understand!!!
#if !defined(GUI_ENABLED) && !defined(UNICODE_ENABLED)
typedef char CONSOLE_FRAME_TYPE;
#elif !defined(GUI_ENABLED) && defined(UNICODE_ENABLED)
typedef unsigned short CONSOLE_FRAME_TYPE;
#endif /*defined(GUI_ENABLED)*/


typedef struct ConsoleRendererCommandsQueue
{
    void* commands_queue;
} ConsoleRendererCommandsQueue;


typedef enum ConsoleRendererCommand
{
    CLEAR_FRAME,
    RENDER_FRAME,
    
    RENDERER_COMMAND_COUNT
} ConsoleRendererCommand;


typedef struct ConsoleSize
{
    // NOTE(Venci): Size of the actual frame to render
    u16 height;
    u16 width;
} ConsoleSize;


typedef struct ConsoleRenderer
{
    ConsoleRendererCommand commands;
    ConsoleSize size; 
    void* frame_data;
#if defined(_WIN32)
    HANDLE console_handler;
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
#elif defined(__linux__)
#endif // defined(_WIN32)
    
} ConsoleRenderer;


SRC_API u16 console_is_key_pressed(u32 virtual_key_code);
SRC_API void console_cursor_hide(ConsoleRenderer* renderer);
SRC_API void console_cursor_begin_move(ConsoleRenderer* renderer);
SRC_API void console_render_frame(ConsoleRenderer* renderer);
SRC_API void console_renderer_destroy(ConsoleRenderer* renderer);
SRC_API ConsoleRenderer* console_renderer_create(u16 screen_height,
                                                 u16 screen_width);
SRC_API void console_make_frame(ConsoleRenderer* renderer, 
                                Snake* snake, 
                                Map* game_map);


#endif /*SNAKE_RENDERER_CONSOLE_WIN*/
