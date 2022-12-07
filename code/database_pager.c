#if defined(_WIN32)
#include <Windows.h>
#endif // defined(_WIN32)

#include <stdio.h>

#include "database_pager.h"
#include "database_package_table.h" // for TABLE_MAX_PAGES, PAGE_SIZE

#include "database_debug.c"


#if defined(_WIN32)
internal LARGE_INTEGER large_integer_cast(u64 value)
{
    LARGE_INTEGER li_value;
#if defined(INT64_MAX)   // Check compiler support
    li_value.QuadPart = (LONGLONG)value;
#else
    li_value.high_part = value & 0xFFFFFFFF00000000;
    li_value.low_part  = value & 0xFFFFFFFF
#endif // defined(INT64_MAX)
    return li_value;
}
#endif // defined(_WIN32)


internal Pager* pager_open(const char* filename)
{
#if defined(_WIN32)
    FILE_DESCRIPTOR file_handler = CreateFileA((LPCSTR)filename, 
                                               GENERIC_READ | GENERIC_WRITE, 
                                               0,
                                               NULL, 
                                               OPEN_ALWAYS, 
                                               0,
                                               NULL);
    
    if (file_handler == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error while opening database table. Error: %d", GetLastError());
        exit(EXIT_FAILURE);
    }
    
    LARGE_INTEGER li_file_size;
    if (!GetFileSizeEx(file_handler, &li_file_size))
    {
        fprintf(stderr, "Error while getting size of the database table. Error: %d", GetLastError());
        CloseHandle(file_handler);
        exit(EXIT_FAILURE);
    }
    
    u64 file_size = (u64)(li_file_size.QuadPart);
#endif // defined(_WIN32)
    Pager* pager = (Pager*)malloc(sizeof(Pager));
    pager->file_handler = file_handler;
    pager->file_size = file_size;
    
    for (u32 i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pager->pages[i] = NULL;
    }

    debug_open_pager(pager);
    return pager;
}


internal void* get_page(Pager* pager, u64 page_num)
{
    if (page_num >= TABLE_MAX_PAGES)
    {
        fprintf(stderr, "Fetching error. Page number (%llu) is out of bound.\n", page_num);
        exit(EXIT_FAILURE);
    }
    u64 num_pages = pager->file_size / PAGE_SIZE;
    
    if (pager->pages[page_num] == NULL)
    {
        void* page = malloc(PAGE_SIZE);
        // Serve space for the part of the file
        if (pager->file_size % PAGE_SIZE != 0)
        {
            num_pages += 1;
        }
        
        if (page_num <= num_pages)
        {
#if defined(_WIN32)
            LARGE_INTEGER page_offset = large_integer_cast(page_num * PAGE_SIZE);
            // Ex stands for extended, just handy version of SetFilePointer
            if (!SetFilePointerEx(pager->file_handler, page_offset, NULL, FILE_BEGIN))
            {
                fprintf(stderr, "Error while fetching database page. Error:%d\n", GetLastError());
                exit(EXIT_FAILURE);
            }
            DWORD bytes_read;
            
            if (!ReadFile(pager->file_handler, (LPVOID)page, PAGE_SIZE, &bytes_read, NULL))
            {
                fprintf(stderr, "Error while reading database page. Error: %d\n", GetLastError());
                exit(EXIT_FAILURE);
            }

            debug_get_page(pager, page_num, bytes_read);
            // Code below make no sense so far
            // if (bytes_read != )
            // {
            //     fprintf(stderr, "Read page size is not equal to page size.\n");
            //     exit(EXIT_FAILURE);
            // }
#endif // defined(_WIN32)
        }
        pager->pages[page_num] = page;
    }
    return pager->pages[page_num];
}


internal void pager_flush(Pager* pager, u64 page_num, u64 size_to_flush)
{
    if (pager->pages[page_num] == NULL)
    {
        fprintf(stderr, "Error while flushing page. Page is NULL.\n");
        exit(EXIT_FAILURE);
    }

#if defined(_WIN32)
    LARGE_INTEGER page_offset = large_integer_cast(page_num * PAGE_SIZE);
    
    if (!SetFilePointerEx(pager->file_handler, page_offset, NULL, FILE_BEGIN))
    {
        fprintf(stderr, "Error while fetching database page. Error: %d\n", GetLastError());
        exit(EXIT_FAILURE);
    }
    DWORD bytes_written;
    
    if (!WriteFile(pager->file_handler, (LPVOID)(pager->pages[page_num]), (DWORD)size_to_flush, &bytes_written, NULL))
    {
        fprintf(stderr, "Error while writing database page. Error: %d\n", GetLastError());
        exit(EXIT_FAILURE);
    }
    
    if (bytes_written != size_to_flush)
    {
        fprintf(stderr, "Error. Page is written partially. (bytes written != size_to_flush).\n");
        exit(EXIT_FAILURE);
    }

    debug_pager_flush(pager, page_num, bytes_written, size_to_flush);
#endif // defined(_WIN32)
}

