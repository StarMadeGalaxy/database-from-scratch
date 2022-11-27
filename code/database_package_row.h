/* date = November 22nd 2022 7:44 pm */

#ifndef DATABASE_PACKAGE_ROW_H
#define DATABASE_PACKAGE_ROW_H

#include "laboratory_work\post_office.h"
#include "laboratory_work\post_package.h"
#include "database_package_table.h"
#include "database_base_types.h"

#define PACKAGE_ID_SIZE StructAttrSize(PackageRow, id)
#define PACKAGE_STREET_SIZE StructAttrSize(PackageRow, package_street)
#define PACKAGE_NAME_SIZE StructAttrSize(PackageRow, package_name)
#define PACKAGE_ID_OFFSET 0
#define PACKAGE_NAME_OFFSET (PACKAGE_ID_OFFSET + PACKAGE_ID_SIZE)
#define PACKAGE_STREET_OFFSET (PACKAGE_NAME_OFFSET + PACKAGE_NAME_SIZE)
#define PACKAGE_ROW_SIZE (PACKAGE_NAME_SIZE + PACKAGE_STREET_SIZE)


typedef struct PackageRow
{
    u64 id;
    char package_name[MAX_PACKAGE_NAME_SIZE + 1];
    char package_street[MAX_STREET_NAME_SIZE + 1];
} PackageRow;


void print_package_row(PackageRow* row)
{
    fprintf(stdout, "\n|Id            : %zu", row->id);
    fprintf(stdout, "\n|Package name  : %s", row->package_name);
    fprintf(stdout, "\n|Package street: %s", row->package_street);
    fprintf(stdout, "\n+--------------------------------------------+\n");
}


void* row_slot(Table* table, u64 row_num)
{
    u64 page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];
    if (page == NULL)
    {
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }
    u64 row_offset = row_num % ROWS_PER_PAGE;
    u64 byte_offset = row_offset * PACKAGE_ROW_SIZE;
    return (u8*)page + byte_offset;
}


void serialize_package_row(PackageRow* source, void* destination)
{
    memcpy((u8*)(destination) + PACKAGE_ID_OFFSET, &(source->id), PACKAGE_ID_SIZE);
    memcpy((u8*)(destination) + PACKAGE_NAME_OFFSET, &(source->package_name), PACKAGE_NAME_SIZE);
    memcpy((u8*)(destination) + PACKAGE_STREET_OFFSET, &(source->package_street), PACKAGE_STREET_SIZE);
}


void deserialize_package_row(void* source, PackageRow* destination)
{
    memcpy(&(destination->id), (u8*)source + PACKAGE_ID_OFFSET, PACKAGE_ID_SIZE);
    memcpy(&(destination->package_name), (u8*)source + PACKAGE_NAME_OFFSET, PACKAGE_NAME_SIZE);
    memcpy(&(destination->package_street), (u8*)source + PACKAGE_STREET_OFFSET, PACKAGE_STREET_SIZE);
}


#endif //DATABASE_PACKAGE_ROW_H
