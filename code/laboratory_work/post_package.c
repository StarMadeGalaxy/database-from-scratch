#include "post_package.h"
#include "database_base_types.h"

typedef enum PackageType
{
    Small, Medium, Large
} PackageType;


typedef struct PostPackage
{
    PackageType type;
    u32 post_office_number;
    char name[MAX_PACKAGE_NAME_SIZE + 1];
} PostPackage; 