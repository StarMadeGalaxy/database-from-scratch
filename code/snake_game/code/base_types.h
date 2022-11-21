
/* date = October 20th 2022 1:59 am */

#ifndef BASE_TYPES_H
#define BASE_TYPES_H


typedef signed char i8;
typedef signed short int i16;
typedef signed int i32;
typedef signed long long int i64;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef signed char b8;

typedef float f32;
typedef double f64;

#define function static
#define internal static
#define global static
#define local static

#define MSB(type) (1 << ((sizeof(type) * 8) - 1))
#define BIT_AMOUNT(type) (sizeof(type) * 8)
#define RAND_RANGE(low, high) (((u16)rand() % (high - low + 1)) + low)
#define COORD_INDEX(x, y, width) (y * width + x)

#define Assert(expression)

#if defined(__cplusplus) && defined(_BITSET_)
# define BITSET_MSB(type) (std::bitset<(BIT_AMOUNT(type))>(MSB(type)))
#endif /* defined(__cplusplus) && defined(_BITSET_) */

#endif //BASE_TYPES_H
