#include "post_office.h"
#include "database_base_types.h"


typedef struct PostOffice
{
    u32 post_office_number;
    u32 packages_number;
    char streets_list[MAX_STREET_NUMBER][MAX_STREET_NAME_SIZE];
} PostOffice;