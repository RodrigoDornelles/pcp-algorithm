#ifndef STR_LIB_PCP_H
#define STR_LIB_PCP_H

#include "types.c"

const char str_txt_tier[4] = "tier";
const char str_txt_head[4] = "head";
const char str_txt_usage[8] = "usage:\n ";
const char str_txt_error[8] = "error:\n ";
const char str_txt_invalid[8] = "invalid ";
const char str_txt_fnnot[16] = "could not open: ";
const char str_txt_end_quote[3] = "\"\n\0";
const char str_txt_end_dot[3] = ".\n\0";
const char str_txt_input[10] = "input file";
const char str_txt_output[11] = "output file";
const char str_txt_help[] =
    "-f <--------- only first\n "
    "-T1 <-------- select tier\n "
    "-o f1.txt <-- output file\n "
    "-i f2.txt <-- input file\n"
;


const char str9_header[] = {'3', '.'};
const char str9_h2 = sizeof(str9_header);

b str2_cmp(const char* txt1, const char* txt2)
{
    return (
        (txt1[0] == txt2[0]) &&
        (txt1[1] == txt2[1])
    );
}

b str9_cmp(const char* txt1, const char* txt2)
{
    return (
        (txt1[0] == txt2[0]) &&
        (txt1[1] == txt2[1]) &&
        (txt1[2] == txt2[2]) &&
        (txt1[3] == txt2[3]) &&
        (txt1[4] == txt2[4]) &&
        (txt1[5] == txt2[5]) &&
        (txt1[6] == txt2[6]) &&
        (txt1[7] == txt2[7]) &&
        (txt1[8] == txt2[8])
    );
}

i8 str9_stack(char* txt, i8 new_char)
{
    i8 old_char = txt[0];
    txt[0] = txt[1];
    txt[1] = txt[2];
    txt[2] = txt[3];
    txt[3] = txt[4];
    txt[4] = txt[5];
    txt[5] = txt[6];
    txt[6] = txt[7];
    txt[7] = txt[8];
    txt[8] = new_char;
    return old_char;
}

b str9_palindrome(char* txt)
{
    return (
        (txt[0] == txt[8]) &&
        (txt[1] == txt[7]) &&
        (txt[2] == txt[6]) &&
        (txt[3] == txt[5])
    );
}

i32 str9_cast(char* txt, i32 value)
{
    int i = 9;
    do {
        i -= 1;
        txt[i] = '0' + (value % 10);
        value = (value / 10);
    }
    while(i);
    return value;
}

#endif
