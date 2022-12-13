#include <stdio.h>    // for fprintf, stdout
#include <string.h>   // for memcpy??
#include <stdlib.h>   // for malloc

#include "database_package_row.h"


internal void print_package_row(PackageRow* row)
{
    fprintf(stdout, "\n|Id            : %zu", row->id);
    fprintf(stdout, "\n|Package name  : %s", row->package_name);
    fprintf(stdout, "\n|Package street: %s", row->package_street);
    fprintf(stdout, "\n+--------------------------------------------+\n");
}


internal void serialize_package_row(PackageRow* source, void* destination)
{
    memcpy((void*)((u8*)(destination) + PACKAGE_ID_OFFSET), (void*)(&(source->id)), PACKAGE_ID_SIZE);
    strncpy((u8*)(destination) + PACKAGE_NAME_OFFSET, source->package_name, PACKAGE_NAME_SIZE);
    strncpy((u8*)(destination) + PACKAGE_STREET_OFFSET, source->package_street, PACKAGE_STREET_SIZE);
}


void deserialize_package_row(void* source, PackageRow* destination)
{
    memcpy((void*)(&destination->id), (void*)((u8*)source + PACKAGE_ID_OFFSET), PACKAGE_ID_SIZE);
    strncpy(destination->package_name, (u8*)source + PACKAGE_NAME_OFFSET, PACKAGE_NAME_SIZE);
    strncpy(destination->package_street, (u8*)source + PACKAGE_STREET_OFFSET, PACKAGE_STREET_SIZE);
}