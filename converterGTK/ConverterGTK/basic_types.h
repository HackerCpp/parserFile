#ifndef BASIC_TYPES_H_
#define BASIC_TYPES_H_

typedef char				char8;
typedef signed char			int8;
typedef unsigned char		uint8;
typedef signed short		int16;
typedef unsigned short		uint16;
typedef signed int			int32;
typedef unsigned int		uint32;
typedef signed long long	int64;
typedef unsigned long long	uint64;

typedef int32				fixed32_3;		/* 32-bit real number with 3 fixed decimal digits */
typedef int32				fixed32_4;		/* 32-bit real number with 4 fixed decimal digits */
typedef int32				fixed32_5;		/* 32-bit real number with 5 fixed decimal digits */
typedef int32				fixed32_6;		/* 32-bit real number with 6 fixed decimal digits */
typedef int32				fixed32_7;		/* 32-bit real number with 7 fixed decimal digits */
typedef uint32				ufixed32_3;		/* unsigned 32-bit real number with 3 fixed decimal digits */
typedef uint32				ufixed32_4;		/* unsigned 32-bit real number with 4 fixed decimal digits */
typedef uint32				ufixed32_5;		/* unsigned 32-bit real number with 5 fixed decimal digits */
typedef uint32				ufixed32_6;		/* unsigned 32-bit real number with 6 fixed decimal digits */
typedef uint32				ufixed32_7;		/* unsigned 32-bit real number with 7 fixed decimal digits */

typedef float				float32;
typedef double				float64;

typedef int32				bool32;

typedef int64				time64;			/* UNIX time format: seconds since 1970-01-01 00:00:00 UTC */

/*
 * void* get_function(char* name) is used by device driver for receiving
 * main program function addresses by name
 */
typedef void* (*GetFunction)(char8* name);

#endif /* BASIC_TYPES_H_ */
