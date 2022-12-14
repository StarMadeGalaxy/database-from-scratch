#include "database_package_table.h"
#include "database_cursor.h"
#include "database_pager.h"


internal DbCursor* table_start(Table* table)
{
    DbCursor* cursor = (DbCursor*)malloc(sizeof(DbCursor));
    cursor->table = table;
    cursor->row_num = 0;
    // If table is empty, so cursor technically at the beginning and at the end of the table at the same time
    cursor->end_of_table = (DbBool)(table->num_rows == 0);

    return cursor;
}


DbCursor* table_end(Table* table)
{
    DbCursor* cursor = (DbCursor*)malloc(sizeof(DbCursor));
    cursor->table = table;
    cursor->row_num = table->num_rows;
    cursor->end_of_table = True;

    return cursor;
}


void* cursor_value(DbCursor* cursor)
{
    u64 row_num = cursor->row_num;
    u64 page_num = row_num / ROWS_PER_PAGE;
    void* page = get_page(cursor->table->pager, page_num);
    u64 row_offset = row_num % ROWS_PER_PAGE;
    u64 byte_offset = row_offset * PACKAGE_ROW_SIZE;
    return (void*)((u8*)page + byte_offset); 
}


void cursor_advance(DbCursor* cursor, i64 offset)
{
    cursor->row_num += offset;

    if (cursor->row_num < 0) 
    {
        cursor->row_num = 0;
    }

    if (cursor->row_num >= cursor->table->num_rows)
    {
        cursor->end_of_table = True;
    }
}