#if !defined(DATABASE_CURSOR_H)
#define DATABASE_CURSOR_H

#include "database_base_types.h"
#include "database_package_table.h"


typedef struct _DbCursor
{
    Table* table;
    u64 row_num;
    DbBool end_of_table;
} DbCursor;


internal DbCursor* table_start(Table* table);
internal DbCursor* table_end(Table* table);
internal void* cursor_value(DbCursor* cursor);
internal void cursor_advance(DbCursor* cursor);


#endif //!defined(DATABASE_CURSOR_H)