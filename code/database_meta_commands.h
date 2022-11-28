#ifndef _META_COMMANDS_H
#define _META_COMMANDS_H

#include "database_repl.h"    // for InputBuffer


typedef enum MetaCommandResult
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


internal MetaCommandResult do_meta_command(InputBuffer* input_buffer);


#endif /* _META_COMMANDS_H */