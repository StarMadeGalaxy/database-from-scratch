/* date = September 25th 2022 2:51 am */

#ifndef DB_BASE_TYPES_H
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

typedef i8 b8;

typedef float f32;
typedef double f64;

#define BYTE(x) (x)
#define KB(x)   ((u64)(1024 * BYTE(x)))
#define MB(x)   ((u64)(1024 * KB(x)))
#define GB(x)   ((u64)(1024 * MB(x)))


#define internal static
#define global static
#define local static

#define StructAttrSize(type, attribute) (sizeof(((type*)0)->attribute))

#endif //DB_BASE_TYPES_H
