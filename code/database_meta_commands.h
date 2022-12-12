#if !defined(_META_COMMANDS_H)
#define _META_COMMANDS_H

#include "database_base_types.h"


typedef struct InputBuffer InputBuffer;


typedef enum MetaCommandResult
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


internal MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table** table);


#endif // !defined(_META_COMMANDS_H)