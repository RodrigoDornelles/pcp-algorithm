#ifndef TYPES_LIB_PCP_H
#define TYPES_LIB_PCP_H

typedef char* s;

typedef unsigned long size_t;

typedef unsigned long uintptr_t;

typedef unsigned long uint64_t;

typedef unsigned int uint32_t;

typedef unsigned int u32;

typedef signed int i32;

typedef unsigned short u16;

typedef unsigned char u8;

typedef signed char i8;

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
