#if !defined(DATABASE_DEBUGGING)
#define DATABASE_DEBUGGING

#if defined(DB_DEBUG)
// headers should be here, but then 
// functions definitions not visible
#endif // defined(DB_DEBUG)


#include <stdio.h>
#include "database_pager.h"
#include "database_package_table.h"
#include "database_base_types.h"
#include "database_package_row.h"
#include "database_cursor.h"
#include "database_repl.h"


internal void debug_input_buffer(InputBuffer* input_buffer)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+INPUT BUFFER DEBUG INFO");
    fprintf(stdout, "|Buffer: %p\n", input_buffer->buffer);
    fprintf(stdout, "|Buffer size: %zu\n", input_buffer->buffer_size);
    fprintf(stdout, "|Input size: %zu\n", input_buffer->input_size);
    fprintf(stdout, "+-------------------------------\n");
#endif // defined(DB_DEBUG)
}


internal void debug_cursor_start(DbCursor* cursor)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Start cursor created\n");
    fprintf(stdout, "|Cursor row num: %llu\n", cursor->row_num);
    fprintf(stdout, "|Cursor end of table: %u\n", cursor->end_of_table);      
    fprintf(stdout, "+--------------------------------------------+\n");  
#endif // defined(DB_MODE)
}


internal void debug_cursor_end(DbCursor* cursor)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+End cursor created\n");
    fprintf(stdout, "|Cursor row num: %llu\n", cursor->row_num);
    fprintf(stdout, "|Cursor end of table: %u\n", cursor->end_of_table);      
    fprintf(stdout, "+--------------------------------------------+\n");  
#endif // defined(DB_MODE)
}


internal void debug_open_db(const char* filename, u64 num_rows)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Opening database\n");
    fprintf(stdout, "|Database has opened a table file with filename: %s\n", filename);
    fprintf(stdout, "|                   Numbers of row in the table: %llu\n", num_rows);      
    fprintf(stdout, "+--------------------------------------------+\n");  
#endif // defined(DB_MODE)
}


internal void debug_print_package_row(void)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Package row information-\n");
    fprintf(stdout, "|            Max Id size : %zu\n", PACKAGE_ID_SIZE);
    fprintf(stdout, "|  Max package name size : %zu\n", PACKAGE_NAME_SIZE);
    fprintf(stdout, "|Max package street size : %zu\n", PACKAGE_STREET_SIZE);
    fprintf(stdout, "|       Package row size : %zu\n", PACKAGE_ROW_SIZE);
    fprintf(stdout, "|    Summed max row size : %zu\n", PACKAGE_ID_SIZE + PACKAGE_NAME_SIZE + PACKAGE_STREET_SIZE);
    fprintf(stdout, "+--------------------------------------------+\n");
    fprintf(stdout, "\n+Page information-\n");
    fprintf(stdout, "|Rows per page: %zu\n", ROWS_PER_PAGE);
    fprintf(stdout, "|Table max row: %zu\n", TABLE_MAX_ROWS);
    fprintf(stdout, "+--------------------------------------------+\n");
#endif // defined(DB_DEBUG)
}


internal void debug_get_page(Pager* pager, u64 page_num, DWORD bytes_read)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Get page-\n");
    fprintf(stdout, "|Page offset : %zu\n", page_num * PAGE_SIZE);
    fprintf(stdout, "| Bytes read : %lu\n", bytes_read);
    fprintf(stdout, "+--------------------------------------------+\n");
#endif // defined(DB_DEBUG)
}


internal void debug_pager_flush(Pager* pager, u64 page_num, DWORD bytes_written, u64 size_to_flush)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Pager flush-\n");
    fprintf(stdout, "|Bytes written : %lu\n", bytes_written);
    fprintf(stdout, "|Size to flush : %zu\n", size_to_flush);
    fprintf(stdout, "|  Page offset : %zu\n", page_num * PAGE_SIZE);
    fprintf(stdout, "+--------------------------------------------+\n");
#endif // defined(DB_DEBUG)
}


#endif // defined(DATABASE_DEBUGGING)