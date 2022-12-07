#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "database_repl.h"
#include "getline.h"
#include "database_debug.c"


internal InputBuffer* new_input_buffer()
{
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    
    if (input_buffer == NULL)
    {
        perror("input_buffer error");
    }
    
    input_buffer->buffer = NULL;
    input_buffer->buffer_size = 0;
    input_buffer->input_size = 0;
    
    return input_buffer;
}


internal void read_input(InputBuffer* input_buffer)
{
    int64_t bytes_read = (int64_t)getline(&(input_buffer->buffer), &(input_buffer->buffer_size), stdin);
    if (bytes_read <= 0)
    {
        perror("read_input error");
    }
    
    /* ignore newline character by from getline function */
    input_buffer->input_size = bytes_read - 1;
    input_buffer->buffer[input_buffer->input_size] = '\0';

    debug_input_buffer(input_buffer);
}


internal void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}


internal void guest_text()
{
    puts("HANDMADE DATABASE FROM SCRATCH");
    puts("CREATED BY VIACHASLAU ILYUK BSUIR 022402");
    puts("FOR LEARNING PURPOSES AND TO COMPLETE TRPOSU");
    puts("LABORATORY WORK IN UNIVERSITY");
    printf("Compiled at: %s %s\n", __DATE__, __TIME__);
}


internal void print_promt()
{
    fputs("\nilyuk_db> ", stdout);
}