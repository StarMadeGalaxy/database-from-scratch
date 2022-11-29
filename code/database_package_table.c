#if defined(_WIN32)
#include <Windows.h>
#endif // defined(_WIN32)

#include "database_package_table.h" // for Table, ROWS_PER_PAGE
#include "database_package_row.h"   // for PACKAGE_ROW_SIZE
#include "database_pager.h"         // for Pager, pager_open()


internal Table* db_open(const char* filename)
{
    Table* table = (Table*)malloc(sizeof(Table));
    Pager* pager = pager_open(filename);
    
    table->num_rows = pager->file_size / PACKAGE_ROW_SIZE;
    table->pager = pager;
    
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
        // pager_flush();
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }
    
    u64 num_additional_rows = table->num_rows % ROWS_PER_PAGE;
    if (num_additional_rows > 0)
    {
        // TODO(Venci): Tomorrow go from there
        u64 last_page = num_full_pages;
    }
    
    for (u64 i = 0; i < TABLE_MAX_PAGES; i++)
    {
        void* page = pager->pages[i];
        if (page != NULL)
        {
            free(page);
            pager->pages[i] = NULL;
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
}

