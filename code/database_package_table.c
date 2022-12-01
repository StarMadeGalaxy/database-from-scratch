#if defined(_WIN32)
#include <Windows.h>
#endif // defined(_WIN32)

#include <stdio.h>

#include "database_package_table.h" // for Table, ROWS_PER_PAGE
#include "database_package_row.h"   // for PACKAGE_ROW_SIZE
#include "database_pager.h"         // for Pager, pager_open()

#include "database_debug.c"


internal Table* db_open(const char* filename)
{
    Table* table = (Table*)malloc(sizeof(Table));
    Pager* pager = pager_open(filename);
    
    table->num_rows = pager->file_size / PACKAGE_ROW_SIZE;
    table->pager = pager;
    
    debug_open_db(filename, table->num_rows);
    return table;
}


internal void db_close(Table* table)
{
    Pager* pager = table->pager;
    u64 num_full_pages = table->num_rows / ROWS_PER_PAGE;
    
    for (u64 i = 0; i < num_full_pages; i++)
    {
        if (pager->pages[i] == NULL)
        {
            continue;
        }
        pager_flush(pager->file_handler, i, PAGE_SIZE);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }
    
    u64 num_additional_rows = table->num_rows % ROWS_PER_PAGE;
    if (num_additional_rows > 0)
    {
        u64 last_page = num_full_pages;
        if (pager->pages[last_page] != NULL)
        {
            pager_flush(pager, last_page, num_additional_rows * PACKAGE_ROW_SIZE);
            free(pager->pages[last_page]);
            pager->pages[last_page] = NULL;
        }
    }
    
    for (u64 i = 0; i < TABLE_MAX_PAGES; i++)
    {
        void* page = pager->pages[i];
        if (page != NULL)
        {
            free(pager->pages[i]);
        }
    }
#if defined(_WIN32)
    if (!CloseHandle(pager->file_handler))
    {
        fprintf(stderr, "Error while closing the table. Error: %d", GetLastError());
        exit(EXIT_FAILURE);
    }
#endif // defined(_WIN32)
    free(pager);
    free(table);
    
    debug_close_db(table, num_full_pages, num_additional_rows);
}
