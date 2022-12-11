/* date = September 25th 2022 2:51 am */

#if !defined(DB_BASE_TYPES_H)
#define DB_BASE_TYPES_H

#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define BYTE(x) (x)
#define KB(x)   ((u64)(1024 * BYTE(x)))
#define MB(x)   ((u64)(1024 * KB(x)))
#define GB(x)   ((u64)(1024 * MB(x)))

#define internal static
#define global static
#define local static

#define UNUSED_PARAMETER(x) ((void)(x))
#define BYTE_PTR(x) ((u8*)(x))

#if defined(_WIN32)
#define MAX_DATABASE_FILENAME_LENGTH 128
#endif // defined(_WIN32)

// database_boolean
typedef u8 DbBool;

#define DbFalse 0
#define DbTrue 1

#if defined(False)
#   undef False
#endif // defined(False)

#if defined(True)
#   undef True
#endif // defined(True)

#define False DbFalse
#define True DbTrue
// database_boolean

#define StructAttrSize(type, attribute) (sizeof(((type*)0)->attribute))

#endif //DB_BASE_TYPES_H
