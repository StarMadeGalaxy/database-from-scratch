#ifndef DATABASE_REPL_H
#define DATABASE_REPL_H

#include "database_base_types.h"


typedef struct _InputBuffer
{
    char* buffer;
    size_t buffer_size;
#if defined(__linux__)
    ssize_t input_size;
#else
    int64_t input_size;
#endif // defined(__linux__)
} InputBuffer;


internal InputBuffer* new_input_buffer();
internal void read_input(InputBuffer* input_buffer);
internal void close_input_buffer(InputBuffer* input_buffer);
internal void input_buffer_debug_print(InputBuffer* input_buffer);
internal void guest_text();
internal void print_promt();

#endif /* _DATABASE_REPL_H */