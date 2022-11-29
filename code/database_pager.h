/* date = November 28th 2022 3:16 pm */

#ifndef DATABASE_PAGER_H
#define DATABASE_PAGER_H

#if defined(_WIN32)
#include <Windows.h>
#endif // defined(_WIN32)

#include "database_package_table.h" // for TABLE_MAX_PAGES


#if defined(_WIN32)
#   define FILE_DESCRIPTOR HANDLE
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

#if defined(_WIN32)
internal LARGE_INTEGER large_integer_cast(u64 value);
#endif // defined(_WIN32)


#endif //DATABASE_PAGER_H
