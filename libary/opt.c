#ifndef OPT_LIB_PCP_H
#define OPT_LIB_PCP_H

#include "math.c"
#include "types.c"
#include "files.c"

u8 u8_opt_get(u8 argc, char ** argv, i8 key, i8 value)
{
    u8 i = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key) {
            value = math2_cast(&argv[i][2]);
            break;
        }
    }

    return value;
}


b has_opt_get(u8 argc, char ** argv, i8 key)
{
    u8 i = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key) {
            return true;
        }
    }

    return false;
}

u8 fn_opt_get(u8 argc, char ** argv, i8 key, i8 value, u16 flags)
{
    u8 i = 0;
    
    for(;i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == key) { 
            /** -i=file.txt**/
            if (argv[i][2] == '=' && argv[i][3] != '\0') {
                value = pcp_open(&argv[i][3], flags);
                break; 
            }
            /** -ifile.txt **/
            if (argv[i][2] != '\0'){
                value = pcp_open(&argv[i][2], flags);
                break;
            }
            /** -i file.txt**/
            if ((i + 1) < argc){
                value = pcp_open(&argv[i+1][0], flags);
                break;
            }
            /** -i **/
            value = pcp9_fn_error;
            break;
        }
    }

    return value;
}

u8 txt_opt_get(u8 argc, char ** argv, i8 key, char * txt)
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
