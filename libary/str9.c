#ifndef STR_9_H
#define STR_9_H

#include "math9.c"

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
        (txt[0] == txt[9]) &&
        (txt[1] == txt[8]) &&
        (txt[2] == txt[7]) &&
        (txt[3] == txt[6]) &&
        (txt[4] == txt[5])
    );
}

#endif
