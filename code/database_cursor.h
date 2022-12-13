#if !defined(DATABASE_CURSOR_H)
#define DATABASE_CURSOR_H

#include "database_base_types.h"


typedef struct Table Table;


typedef struct DbCursor
{
    Table* table;
    u64 row_num;
    DbBool end_of_table;
} DbCursor;


internal DbCursor* table_start(Table* table);
DbCursor* table_end(Table* table);
void* cursor_value(DbCursor* cursor);
void cursor_advance(DbCursor* cursor, i64 offset);


#endif //!defined(DATABASE_CURSOR_H)