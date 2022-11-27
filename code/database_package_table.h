/* date = November 23rd 2022 11:20 pm */

#ifndef DATABASE_PACKAGE_TABLE_H
#define DATABASE_PACKAGE_TABLE_H

#include "database_base_types.h"
#include "database_package_row.h"
#include <stdlib.h>

#define PAGE_SIZE KB(4)
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE ((u64)(PAGE_SIZE / PACKAGE_ROW_SIZE))
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)


typedef struct Table
{
    u64 num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;


Table* new_table()
{
    Table* table = (Table*)malloc(sizeof(Table));
    table->num_rows = 0;
    for (u64 i = 0; i < TABLE_MAX_PAGES; i++)
    {
        table->pages[i] = NULL;
    }
    return table;
}


void free_table(Table* table)
{
    for (u64 i = 0; i < TABLE_MAX_PAGES; i++)
    {
        free(table->pages[i]);
    }
    free(table);
}


#endif //DATABASE_PACKAGE_TABLE_H
