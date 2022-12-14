//C:\Program Files (x86)\Windows Kits\10\include\10.0.19041.0\um\winbase.h(9531):
//warning C5105: macro expansion producing 'defined' has undefined behavior
#pragma warning(disable : 5105)


#include <stdlib.h> // EXIT_FAILURE, EXIT_SUCCESS
#include <stdio.h>
#include <string.h>

// Unity build?
#include "laboratory_work\post_package.c"
#include "laboratory_work\post_office.c"
#include "database_package_table.c"
#include "database_meta_commands.c"
#include "database_package_row.c"
#include "database_statement.c"
#include "database_cursor.c"
#include "database_pager.c"
#include "database_repl.c"

#include "database_debug.c"


int main(int argc, char* argv[])
{
#if !defined(_WIN32) && !defined(__linux__)
    fprintf(stderr, "Platform is not supported!\n");
    exit(EXIT_FAILURE);
#endif //!defined(_WIN32) && !defined(__linux__)

    if (argc >= 2)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            help_text();
            fputc('\n', stdout);
        }
        else 
        {
            fprintf(stderr, "Unrecognized command line argument.\n");
        }
    }


    guest_text();
    InputBuffer* input_buffer = new_input_buffer();
    //Table* table = db_open(argv[1]);
    Table* table = NULL;

    debug_print_package_row();
    
    /* Main loop */
    for (;;)
    { 
        print_promt();
        read_input(input_buffer);
        
        if (input_buffer->buffer[0] == '$')
        {
            switch (do_meta_command(input_buffer, &table))
            {
                case META_COMMAND_SUCCESS:
                {
                    continue;
                }
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                {
                    fprintf(stdout, "\nUnrecognized command '%s'.\n", input_buffer->buffer);
                    continue;
                }
                default:
                {
                    fprintf(stderr, "Error. Do meta command unrecognized return value.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
            case PREPARE_STATEMENT_SUCCESS:
            {
                break;
            }
            case PREPARE_NEGATIVE_ID:
            {
                fprintf(stderr, "Error. Id couldn't be a negative number.\n");
                continue;
            }
            case PREPARE_STRING_TOO_LONG:
            {
                fprintf(stderr, "Error. At least one of the arguments is too long.\n");
                continue;
            }
            case PREPARE_STRING_TOO_SHORT:
            {
                fprintf(stderr, "Error. At least one of the arguments is too short.\n");
                continue;
            }
            case PREPARE_UNRECOGNIZED_DATABASE_FILE:
            {
                fprintf(stderr, "Error. Invalid database file.\n");
                continue;
            }
            case PREPARE_UNRECOGNIZED_STATEMENT:
            {
                fprintf(stderr, "Error. Unrecognized statement at start of '%s'\n", input_buffer->buffer);
                continue;
            }
            case PREPARE_SYNTAX_ERROR:
            {
                fprintf(stderr, "Syntax error. Could not parse statement.\n");
                continue;
            }
            default:
            {
                fprintf(stderr, "Error. Prepare statement unrecognized return value.\n");
                exit(EXIT_FAILURE);
            }
        }
        
        switch(execute_statement(&statement, &table))
        {
            case EXECUTE_SUCCESS:
            {
                fprintf(stdout, "Executed successfully.\n");
                break;
            }
            case EXECUTE_TABLE_FULL:
            {
                fprintf(stdout, "Error: table full.\n");
                break;
            }
            case EXECUTE_DATABASE_FILE_NOT_LOADED:
            {
                fprintf(stderr, "Error. Database file is not loaded. Please run READ [<filename>.idb].\n");
                continue;
            }
            default:
            {
                fprintf(stderr, "Error. Execute statement unrecognized return value.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    close_input_buffer(input_buffer);
    free(table);
    return EXIT_SUCCESS;
}