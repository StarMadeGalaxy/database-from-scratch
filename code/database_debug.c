#if !defined(DATABASE_DEBUGGING)
#define DATABASE_DEBUGGING


#if defined(DB_DEBUG)
#include <stdio.h>
#include "database_pager.h"
#include "database_package_table.h"
#include "database_base_types.h"
#include "database_package_row.h"
#endif // defined(DB_DEBUG)


internal void debug_open_db(const char* filename, u64 num_rows)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Opening database\n");
    fprintf(stdout, "|Database has opened a table file with filename: %s\n", filename);
    fprintf(stdout, "|                   Numbers of row in the table: %llu\n", num_rows);      
    fprintf(stdout, "+--------------------------------------------+\n");  
#endif // defined(DB_MODE)
}


internal void debug_open_pager(Pager* pager)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Opening pager\n");
    fprintf(stdout, "|File size opened by the pager: %llu\n", pager->file_size);
    fprintf(stdout, "+--------------------------------------------+\n");
#endif`// defined(DB_MODE)
}


internal void debug_close_db(Table* table, u64 num_full_pages, u64 num_add_row)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Closing database-\n");
    fprintf(stdout, "|Number of additional rows: %llu\n", num_add_row);
    fprintf(stdout, "|     Number of full pages: %llu\n\n", num_full_pages);
    fprintf(stdout, "+--------------------------------------------+\n");
    system("PAUSE");
#endif // defined(DB_MODE)
}


internal void debug_print_package_row(void)
{
#if defined(DB_DEBUG)
    fprintf(stdout, "\n+Package row information-\n");
    fprintf(stdout, "|Max Id size             : %zu\n", PACKAGE_ID_SIZE);
    fprintf(stdout, "|Max package name size   : %zu\n", PACKAGE_NAME_SIZE);
    fprintf(stdout, "|Max package street size : %zu\n", PACKAGE_STREET_SIZE);
    fprintf(stdout, "|       Package row size : %zu\n", PACKAGE_ROW_SIZE);
    fprintf(stdout, "|    Summed max row size : %zu\n", PACKAGE_ID_SIZE + PACKAGE_NAME_SIZE + PACKAGE_STREET_SIZE);
    fprintf(stdout, "+--------------------------------------------+\n");
    fprintf(stdout, "\n+Page information-\n");
    fprintf(stdout, "|Rows per page: %zu\n", ROWS_PER_PAGE);
    fprintf(stdout, "|Table max row: %zu\n", TABLE_MAX_ROWS);
    fprintf(stdout, "+--------------------------------------------+\n");
#endif // defined(DB_DEBUG)
}


#endif // defined(DATABASE_DEBUGGING)