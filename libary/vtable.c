#ifndef VTABLE_LIB_PCP
#define VTABLE_LIB_PCP

#include "str.c"
#include "math.c"
#include "types.c"

#define VT_MIN_TIER 1
#define VT_MAX_TIER 2

#ifndef VT_IDEAL_SIZE
#define VT_IDEAL_SIZE 22
#endif

struct vtable_funcs_s {
    u8 size;
    u128 (*int_from_str)(char*);
    b (*int_cousin)(u128);
    b (*str_cmp)(char*, char*);
    i8 (*str_stack)(char*, i8);
    u128 (*str_from_int)(char*, u128);
    b (*str_palindrome)(char*);
};

typedef const struct vtable_funcs_s* fvt;

static const struct vtable_funcs_s vtable[] = {
    {
        .size = 9,
        .int_from_str = &math9_cast,
        .int_cousin = &math_cousin,
        .str_cmp = &str9_cmp,
        .str_stack = &str9_stack,
        .str_from_int = &str9_cast,
        .str_palindrome = &str9_palindrome
    },
    {
        .size = 21,
        .int_from_str = &math21_cast,
        .int_cousin = &math_cousin,
        .str_cmp = &str21_cmp,
        .str_stack = &str21_stack,
        .str_from_int = &str21_cast,
        .str_palindrome = &str21_palindrome
    }
};

fvt vt_tier(u8 tier)
{
    return &vtable[tier - 1];
}

#endif
