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

b str9_palindrome(const char* txt)
{
    return (
        (txt[0] == txt[8]) &&
        (txt[1] == txt[7]) &&
        (txt[2] == txt[6]) &&
        (txt[3] == txt[5])
    );
}

#endif
