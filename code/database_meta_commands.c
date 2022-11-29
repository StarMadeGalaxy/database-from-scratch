#include "database_meta_commands.h"
#include "database_package_table.h" // for Table and free_table()
#include "snake_game\code\snake_game.h" // for snake_game_start()


internal MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table)
{
    if (strcmp(input_buffer->buffer, "$exit") == 0)
    {
        close_input_buffer(input_buffer);
        db_close(table);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(input_buffer->buffer, "$ilyuk_game") == 0)
    {
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