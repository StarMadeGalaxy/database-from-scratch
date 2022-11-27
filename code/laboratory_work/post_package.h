/* date = November 22nd 2022 6:59 pm */

#ifndef POST_PACKAGE_H
#define POST_PACKAGE_H

#define MAX_PACKAGE_NAME_SIZE 64

#include "post_office.h"


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


#endif //POST_PACKAGE_H
