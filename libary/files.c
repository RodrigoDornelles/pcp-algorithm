#ifndef FILES_LIB_PCP_H
#define FILES_LIB_PCP_H

#if defined(_USE_STD)
#include <unistd.h>
#include <fcntl.h>

u32 pcp_open(any_const pointer, u32 flags)
{
    return open(pointer, flags);
}

u32 pcp_write(u8 fileno, any_const pointer, u32 size)
{
    return write(fileno, pointer, size);
}

u32 pcp_read(u8 fileno, any_const pointer, u32 size)
{
    return read(fileno, pointer, size);
}

#else 
const u32 STDIN_FILENO = 0u;
const u32 STDOUT_FILENO = 1u;
const u32 STDERR_FILENO = 2u;
const u32 O_RDONLY = 0x000u;
const u32 O_CREAT =  0x200u;
const u32 O_WRONLY = 0x001u;

#if defined(__x86_64__) && defined(__APPLE__)
u32 pcp_open(any_const pointer, u32 flags)
{
    u32 ret;
    asm("syscall"
        : "=a"(ret)
        :"0"(0x2000005),
        "b"(pointer),
        "c"(flags)
        :"memory"
    );
    return ret;
}

u32 pcp_write(u8 fileno, any_const pointer, u32 size)
{
    u32 ret;
    asm("syscall"
        : "=a"(ret)
        :"0"(0x2000004),
        "b"(fileno),
        "c"(pointer),
        "d"(size)
        :"memory"
    );
    return ret;
}

u32 pcp_read(u8 fileno, any_const pointer, u32 size)
{
    u32 ret;
    asm("syscall"
        : "=a"(ret)
        :"0"(0x2000003),
        "b"(fileno),
        "c"(pointer),
        "d"(size)
        :"memory"
    );
    return ret;
}

#elif defined(__x86_64__) && defined(__linux__)

u32 pcp_open(any_const pointer, u32 flags)
{
    u32 ret;
    asm("syscall"
        :"=a"(ret)
        :"0"(2),
        "D"(pointer),
        "S"(flags)
        :"memory"
    );
    return ret;
}

u32 pcp_write(u8 fileno, any_const pointer, u32 size)
{
    u32 ret;
    asm("syscall"
        :"=a"(ret)
        :"0"(1),
        "D"(fileno),
        "S"(pointer),
        "d"(size)
        :"memory"
    );
    return ret;
}

u32 pcp_read(u8 fileno, any_const pointer, u32 size)
{
    u32 ret;
    asm("syscall"
        :"=a"(ret)
        :"0"(0),
        "D"(fileno),
        "S"(pointer),
        "d"(size)
        :"memory"
    );
    return ret;
}
#else
#error the system is not supported.
#endif
#endif
#endif
