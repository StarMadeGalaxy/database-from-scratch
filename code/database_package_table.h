/* date = November 23rd 2022 11:20 pm */

#ifndef DATABASE_PACKAGE_TABLE_H
#define DATABASE_PACKAGE_TABLE_H

#include <stdlib.h>
#include "database_base_types.h"
#include "database_package_row.h"

#define PAGE_SIZE KB(4)
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE ((u64)(PAGE_SIZE / PACKAGE_ROW_SIZE))
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)


typedef struct Table
{
    u64 num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;



internal Table* new_table();
internal void free_table(Table* table);


#endif //DATABASE_PACKAGE_TABLE_H
