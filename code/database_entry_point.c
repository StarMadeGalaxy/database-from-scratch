#include <stdio.h>
#include <string.h>

#include "database_repl.h"
#include "database_meta_commands.h"
#include "database_statament.h"

int main(int argc, char* argv[])
{
    guest_text();
    InputBuffer* input_buffer = new_input_buffer();
    
    /* Main loop */
    for (;;)
    { 
        print_promt();
        read_input(input_buffer);
        if (input_buffer->buffer[0] == '$')
        {
            switch (do_meta_command(input_buffer))
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
                
            }
            case PREPARE_UNRECOGNIZED_STATEMENT:
            {
                
            }
        }
    }
    
    close_input_buffer(input_buffer);
    return EXIT_SUCCESS;
}