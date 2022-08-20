#ifndef STR_9_H
#define STR_9_H

#include "types9.c"

const char str9_txt_error[9] = "error:\n ";
const char str9_txt_fnnot[15] = "could not open ";
const char str9_txt_input[10] = "input file";
const char str9_txt_output[11] = "output file";
const char str9_txt_invalid[10] = "is invalid";
const char str9_txt_end_dot[] = ".\n";
const char str9_txt_end_quote[] = "\"\n";
const char str9_txt_help[] =
    "usage:\n"
    " -h <----------- help\n"
    " -f <----------- first\n"
    " -ofile1.txt <-- output\n"
    " -ifile2.txt <-- input\n"
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
