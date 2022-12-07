/* date = November 23rd 2022 11:20 pm */

#ifndef DATABASE_PACKAGE_TABLE_H
#define DATABASE_PACKAGE_TABLE_H

#include "database_base_types.h"


typedef struct Table Table;


internal Table* new_table();
internal void db_close(Table* table);
internal Table* db_open(const char* filename);


#endif //DATABASE_PACKAGE_TABLE_H
