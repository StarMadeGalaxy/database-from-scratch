#include "database_package_table.h"


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
