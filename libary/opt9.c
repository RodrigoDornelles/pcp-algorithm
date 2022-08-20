#ifndef OPT_9_H
#define OPT_9_H

#include "types9.c"

u8 u8_opt9_get(u8 argc, s* argv, i8 key, i8 value)
{
    u8 i = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key) {
            value = argv[i][2] - '0';
            break;
        }
    }

    return value;
}


b has_opt9_get(u8 argc, s* argv, i8 key)
{
    u8 i = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key) {
            return true;
        }
    }

    return false;
}

u8 fn_opt9_get(u8 argc, s* argv, i8 key, i8 value, u16 flags)
{
    u8 i = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key) {   
            value = open(&argv[i][2], flags);
            break;
        }
    }

    return value;
}

u8 txt_opt9_get(u8 argc, s* argv, i8 key, s txt)
{
    u8 i = 0, size = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key){
            while(argv[i][size+2] != '\0') {
                txt[size] = argv[i][size + 2];
                size++;
            }
            break;
        }
    }

    return size;
}


#endif
