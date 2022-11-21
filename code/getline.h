/* date = October 13th 2022 1:13 am 

My win implementation of the POSIX getline
 reading from console input buffer using winapi
Returns the number of characters read (not including the
   null terminator), or -1 on error or EOF.  

Function with double underscore before and after the name
like: "__function__", means function the is not intended to
be called manually.

*/

#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdlib.h>
#include <stdio.h> /* for standard getline */
#include <errno.h>

#ifdef U64_MAX
#undef U64_MAX
#endif /* U64_MAX */

#ifdef _WIN32
#include <stdint.h>
#define U64_MAX SIZE_MAX
typedef size_t u64;
typedef int64_t i64;
#endif /* _WIN32*/

#ifdef __linux__
#include <sys/types.h> /* for ssize_t */
#define U64_MAX SSIZE_MAX
typedef ssize_t i64;
#endif /* __linux__ */

static i64 __getline__(char** lineptr, u64* buffer_size, FILE* stream);
static i64 __getdelim__(char** lineptr, u64* buffer_size, char delim, FILE* stream);

static i64 __getline__(char** lineptr, u64* buffer_size, FILE* stream)
{
#ifdef _WIN32
    return __getdelim__(lineptr, buffer_size, '\n', stream);
#else /* call posix getline */
    return getline(lineptr, buffer_size, stream);
#endif /* _WIN32 */
}


#ifdef _WIN32
static i64 __freadline__(char* buffer, u64 size, u64 buf_size, FILE* stream);


static i64 __getdelim__(char** lineptr, u64* buffer_size, char delim,     FILE* stream)
{
    u64 cur_len = 0;
    u64 len;
    
    if (lineptr == NULL || buffer_size == NULL )
    {
        _set_errno(EINVAL);
        return -1;
    }
    
    if (ferror(stream) || feof(stream))
        return -1;
    
    if (*lineptr == NULL || *buffer_size  == 0)
    {
        *buffer_size = 120;
        *lineptr = (char*)malloc(*buffer_size);
        if (*lineptr == NULL)
            return -1;
    }
    
    for(;;)
    {
        u64 needed;      /* to reallocate */
        char* t; 
        
        char* start_ptr = *lineptr + (cur_len * sizeof(char));
        u64 added_size = *buffer_size - cur_len;
        
        len = __freadline__(start_ptr, sizeof(char), added_size, stream);
        t = (char*)memchr((void*)*lineptr, delim, *buffer_size);
        if (len >= U64_MAX - cur_len)    /* = unable to add '\0' */
        {
            _set_errno(EOVERFLOW);
            return -1;
        }
        
        needed = cur_len + len + 1;
        if (needed > *buffer_size)
        {
            char* new_lineptr;
            if (needed < *buffer_size * 2) /* why do we need this? */
                needed = *buffer_size * 2;
            
            new_lineptr = (char*)realloc(*lineptr, needed);
            if (new_lineptr == NULL)
                return -1;
            
            *lineptr = new_lineptr;
            *buffer_size = needed;
        }
        cur_len += len;
        if (t != NULL)
            break;
    }
    (*lineptr)[cur_len] = '\0';
    return cur_len;
}

/*
 Function: __freadline__
Reads  from a stream till newline is met.
 Returns number of elements read including newline.
Do not terminate a string.
*/
static i64 __freadline__(char* buffer, u64 size, u64 buf_size, FILE* stream)
{
    if (buffer == NULL || size == 0 || buf_size == 0 || stream == NULL)
    {
        _set_errno(EINVAL);
        return -1;
    }
    
    if (ferror(stream) || feof(stream))
        return -1;
    
    i64 how_much_read = 0;
    for (u64 i = 0; i < buf_size; i++)
    {
        u64 nread = fread(&buffer[i], sizeof(char), 1, stream);
        how_much_read += nread;
        if (buffer[i] == '\n')
            break;
    }
    return how_much_read;
}


#define getline __getline__
#endif /* _WIN32 */
// TODO(Venci): implement __freadlinew__ for wchar_t
#endif /*_GETLINE_H */
