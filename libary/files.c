#ifndef FILES_LIB_PCP_H
#define FILES_LIB_PCP_H

#if defined(_USE_STD)
#include <unistd.h>
#include <fcntl.h>
#else
const u32 STDIN_FILENO = 0u;
const u32 STDOUT_FILENO = 1u;
const u32 STDERR_FILENO = 2u;
const u32 O_RDONLY = 0x000u;
const u32 O_CREAT =  0x200u;
const u32 O_WRONLY = 0x001u;
#endif

u32 pcp_open(any_const pointer, u32 flags)
{
#if defined(_USE_STD)
    return open(pointer, flags);
#else
    u32 ret;
    asm("syscall"
        : "=a"(ret)
#if defined(__APPLE__)
        :"0"(0x2000005),
#elif defined(__linux__)
        :"0"(2),
#endif
        "b"(pointer),
        "c"(flags)
        :"memory"
    );
    return ret;
#endif
}

u32 pcp_write(u8 fileno, any_const pointer, u32 size)
{
#if defined(_USE_STD)
    return write(fileno, pointer, size);
#else
    u32 ret;
    asm("syscall"
        : "=a"(ret)
#if defined(__APPLE__)
        :"0"(0x2000004),
#elif defined(__linux__)
        :"0"(1),
#endif
        "b"(fileno),
        "c"(pointer),
        "d"(size)
        :"memory"
    );
    return ret;
#endif
}

u32 pcp_read(u8 fileno, any_const pointer, u32 size)
{
#if defined(_USE_STD)
    return read(fileno, pointer, size);
#else
    u32 ret;
    asm("syscall"
        : "=a"(ret)
#if defined(__APPLE__)
        :"0"(0x2000003),
#elif defined(__linux__)
        :"0"(3),
#endif
        "b"(fileno),
        "c"(pointer),
        "d"(size)
        :"memory"
    );
    return ret;
#endif
}

#endif
