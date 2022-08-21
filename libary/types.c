#ifndef TYPES_LIB_PCP_H
#define TYPES_LIB_PCP_H

typedef unsigned __int128 u128;
typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef __int128 i128;
typedef long i64;
typedef int i32;
typedef short i16;
typedef char i8;

typedef unsigned char fn;

typedef void* any;

typedef const void* any_const;

const u8 pcp9 = 9;
const fn pcp9_fn_error = -1;
const fn pcp9_exit_error = 15;

enum bu {
    false = (u8) 0u,
    true = (u8) 1u
};

typedef enum bu b;

#endif
