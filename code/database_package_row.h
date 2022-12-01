/* date = November 22nd 2022 7:44 pm */

#ifndef DATABASE_PACKAGE_ROW_H
#define DATABASE_PACKAGE_ROW_H

#include "laboratory_work\post_office.h"   // for MAX_STREET_NAME_SIZE 
#include "laboratory_work\post_package.h"  // for MAX_PACKAGE_NAME_SIZE 
#include "database_package_table.h"        // for Table
#include "database_base_types.h"           // for u64 u8

#define PACKAGE_ID_SIZE StructAttrSize(PackageRow, id)
#define PACKAGE_STREET_SIZE StructAttrSize(PackageRow, package_street)
#define PACKAGE_NAME_SIZE StructAttrSize(PackageRow, package_name)
#define PACKAGE_ID_OFFSET 0
#define PACKAGE_NAME_OFFSET (PACKAGE_ID_OFFSET + PACKAGE_ID_SIZE)
#define PACKAGE_STREET_OFFSET (PACKAGE_NAME_OFFSET + PACKAGE_NAME_SIZE)
#define PACKAGE_ROW_SIZE (PACKAGE_NAME_SIZE + PACKAGE_STREET_SIZE + PACKAGE_ID_SIZE)


typedef struct _PackageRow
{
    u64 id;
    char package_name[MAX_PACKAGE_NAME_SIZE + 1];
    char package_street[MAX_STREET_NAME_SIZE + 1];
} PackageRow;


internal void print_package_row(PackageRow* row);
internal void* row_slot(Table* table, u64 row_num);
internal void serialize_package_row(PackageRow* source, void* destination);
internal void deserialize_package_row(void* source, PackageRow* destination);


#endif //DATABASE_PACKAGE_ROW_H
