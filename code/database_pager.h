/* date = November 28th 2022 3:16 pm */

#ifndef DATABASE_PAGER_H
#define DATABASE_PAGER_H

#include "database_package_table.h" // for TABLE_MAX_PAGES

#define PAGE_SIZE KB(4)
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE ((u64)(PAGE_SIZE / PACKAGE_ROW_SIZE))
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

#if defined(_WIN32)
#   define FILE_DESCRIPTOR void*    // HANDLE is void*
#else 
#   define FILE_DESCRIPTOR int
#endif // defined(_WIN32)


typedef struct Pager 
{
    FILE_DESCRIPTOR file_handler;
    u64 file_size;
    void* pages[TABLE_MAX_PAGES];
} Pager;


internal Pager* pager_open(const char* filename);
internal void* get_page(Pager* pager, u64 page_num);
internal void pager_flush(Pager* pager, u64 page_size, u64 size);


#endif //DATABASE_PAGER_H
