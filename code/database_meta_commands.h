#ifndef _META_COMMANDS_H
#define _META_COMMANDS_H

#include "snake_game\code\snake_game.h"


typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
    if (strcmp(input_buffer->buffer, "$exit") == 0)
    {
        exit(EXIT_SUCCESS);
        return META_COMMAND_SUCCESS;
    }
    else if (strcmp(input_buffer->buffer, "$ilyuk_game") == 0)
    {
        snake_game_start();
        fflush(stdout);
        return META_COMMAND_SUCCESS;
    }
    else if (strcmp(input_buffer->buffer, "$cls") == 0)
    {
#if defined(_WIN32)
        system("cls");
#elif defined(__linux__);
        system("clear");
#endif // defined(_WIN32)
        return META_COMMAND_SUCCESS;
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

#endif /* _META_COMMANDS_H */