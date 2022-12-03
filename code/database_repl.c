#include "database_repl.h"


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
}


internal void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}


internal void input_buffer_debug_print(InputBuffer* input_buffer)
{
#if defined(DB_DEBUG)
    puts("\n----INPUT BUFFER DEBUG INFO----");
    printf("\nBuffer: %p", input_buffer->buffer);
    printf("\nBuffer size: %zu", input_buffer->buffer_size);
    printf("\nInput size: %zu", input_buffer->input_size);
    puts("\n-------------------------------\n");
#endif // defined(DB_DEBUG)
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