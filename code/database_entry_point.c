//C:\Program Files (x86)\Windows Kits\10\include\10.0.19041.0\um\winbase.h(9531):
//warning C5105: macro expansion producing 'defined' has undefined behavior
#pragma warning(disable : 5105)

#include <stdio.h>
#include <string.h>

#include "database_repl.h"
#include "database_meta_commands.h"
#include "database_statament.h"
#include "database_package_table.h"

int main(int argc, char* argv[])
{
    guest_text();
    InputBuffer* input_buffer = new_input_buffer();
    Table* table = new_table();
    
    /* Main loop */
    for (;;)
    { 
        print_promt();
        read_input(input_buffer);
        
        if (input_buffer->buffer[0] == '$')
        {
            switch (do_meta_command(input_buffer, table))
            {
                case META_COMMAND_SUCCESS:
                {
                    continue;
                }
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                {
                    printf("\nUnrecognized command '%s'.\n", input_buffer->buffer);
                    continue;
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
                printf("Id couldn't be a negative number.\n");
                continue;
            }
            case PREPARE_STRING_TOO_LONG:
            {
                printf("At least one of the arguments is too long as my pp.\n");
                continue;
            }
            case PREPARE_UNRECOGNIZED_STATEMENT:
            {
                printf("Unrecognized statement at start of '%s'\n", input_buffer->buffer);
                continue;
            }
            case PREPARE_SYNTAX_ERROR:
            {
                printf("Syntax error. Could not parse statement.\n");
                continue;
            }
        }
        
        switch(execute_statement(&statement, table))
        {
            case EXECUTE_SUCCESS:
            {
                printf("Executed successfully.\n");
                break;
            }
            case EXECUTE_TABLE_FULL:
            {
                printf("Error: table full.\n");
                break;
            }
        }
    }
    
    close_input_buffer(input_buffer);
    free(table);
    return EXIT_SUCCESS;
}