#ifndef HBASE
#define HBASE

#include <stdio.h>

typedef unsigned long long	u64;
typedef signed long long	s64;

typedef unsigned int		u32;
typedef signed int			s32;

typedef unsigned short		u16;
typedef signed short		s16;

typedef unsigned char		u8;
typedef signed char			s8;

typedef float				f32;

typedef u64					quant64;
typedef u32					quant32;
typedef u16					quant16;
typedef u8					quant8;

typedef u64					index64;
typedef u32					index32;

typedef u64					mask64;
typedef u32					mask32;
typedef	u8					mask8;

typedef u64					hash64;
typedef u32					hash32;

typedef u32					bool32;
typedef u8					bool8;

typedef u32					ret32;

#endif

#define PACKED __attribute__((packed))
#define PADDING(bytes) u8 padding[bytes]

#endif
