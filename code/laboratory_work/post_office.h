/* date = November 22nd 2022 6:53 pm */

#ifndef POST_OFFICE_H
#define POST_OFFICE_H

#define MAX_STREET_NUMBER 3
#define MAX_STREET_NAME_SIZE 64


typedef struct PostOffice
{
    u32 post_office_number;
    u32 packages_number;
    char streets_list[MAX_STREET_NUMBER][MAX_STREET_NAME_SIZE];
} PostOffice;


#endif //POST_OFFICE_H
