#if defined(_WIN32)
#include <Windows.h>
#endif // defined(_WIN32)

#include <stdio.h>
#include <stdlib.h>

#include "database_package_table.h" // for Table, ROWS_PER_PAGE
#include "database_package_row.h"   // for PACKAGE_ROW_SIZE
#include "database_pager.h"         // for Pager, pager_open()

#include "database_debug.c"


// DATABASE DEBUG
internal void debug_close_table(Table* table);
// DATABASE DEBUG


internal Table* db_open(const char* filename)
{
    Table* table = (Table*)malloc(sizeof(Table));
    u64 file_size;
    Pager* pager = pager_open(filename, &file_size);
    
    table->num_rows = file_size / PACKAGE_ROW_SIZE;
    table->pager = pager;
    
    debug_open_db(filename, table->num_rows);
    return table;
}


internal void db_close(Table* table)
{
    Pager* pager = table->pager;
    pager_close(pager, table->num_rows);
    free(table);
    
    debug_close_table(table);
}


internal void debug_close_table(Table* table)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Closing table-\n");
    fprintf(stdout, "|Number of rows in the current table: %llu\n", table->num_rows);
    fprintf(stdout, "+--------------------------------------------+\n");
    system("PAUSE");
#endif // defined(DB_MODE)
}

