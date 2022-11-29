#include <stdio.h>    // for fprintf, stdout
#include <string.h>   // for memcpy??
#include <stdlib.h>   // for malloc

#include "database_package_row.h"
#include "database_package_table.h"


internal void print_package_row(PackageRow* row)
{
    fprintf(stdout, "\n|Id            : %zu", row->id);
    fprintf(stdout, "\n|Package name  : %s", row->package_name);
    fprintf(stdout, "\n|Package street: %s", row->package_street);
    fprintf(stdout, "\n+--------------------------------------------+\n");
}


internal void* row_slot(Table* table, u64 row_num)
{
    void* page = get_page(table->pager, row_num);
    u64 page_num = row_num / ROWS_PER_PAGE;
    u64 row_offset = row_num % ROWS_PER_PAGE;
    u64 byte_offset = row_offset * PACKAGE_ROW_SIZE;
    return (void*)((u8*)page + byte_offset);
}


internal void serialize_package_row(PackageRow* source, void* destination)
{
    memcpy((u8*)(destination) + PACKAGE_ID_OFFSET, &(source->id), PACKAGE_ID_SIZE);
    memcpy((u8*)(destination) + PACKAGE_NAME_OFFSET, &(source->package_name), PACKAGE_NAME_SIZE);
    memcpy((u8*)(destination) + PACKAGE_STREET_OFFSET, &(source->package_street), PACKAGE_STREET_SIZE);
}


internal void deserialize_package_row(void* source, PackageRow* destination)
{
    memcpy(&(destination->id), (u8*)source + PACKAGE_ID_OFFSET, PACKAGE_ID_SIZE);
    memcpy(&(destination->package_name), (u8*)source + PACKAGE_NAME_OFFSET, PACKAGE_NAME_SIZE);
    memcpy(&(destination->package_street), (u8*)source + PACKAGE_STREET_OFFSET, PACKAGE_STREET_SIZE);
}