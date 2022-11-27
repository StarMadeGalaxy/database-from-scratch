#ifndef _META_COMMANDS_H
#define _META_COMMANDS_H

#include "snake_game\code\snake_game.h"
#include "database_package_table.h"


typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table)
{
    if (strcmp(input_buffer->buffer, "$exit") == 0)
    {
        close_input_buffer(input_buffer);
        free_table(table);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(input_buffer->buffer, "$ilyuk_game") == 0)
    {
        close_input_buffer(input_buffer);
        snake_game_start();
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