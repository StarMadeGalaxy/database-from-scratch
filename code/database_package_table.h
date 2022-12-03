/* date = November 23rd 2022 11:20 pm */

#ifndef DATABASE_PACKAGE_TABLE_H
#define DATABASE_PACKAGE_TABLE_H

#include "database_base_types.h"
#include "database_pager.h"


typedef struct Table
{
    u64 num_rows;
    Pager* pager;
} Table;


internal Table* new_table();
internal void db_close(Table* table);
internal Table* db_open(const char* filename);


#endif //DATABASE_PACKAGE_TABLE_H
