#ifndef MATH_LIB_PCP_H
#define MATH_LIB_PCP_H

#include "types.c"

i8 math2_cast(char* txt)
{
	i8 res = (txt[0] - '0');
	if (txt[1] != '\0') {
		res *= 10;
		res += (txt[1] - '0');
	}
	return res;
}

u128 math9_cast(char* txt)
{
    return (
        ((txt[0] - '0') * 100000000u) + 
        ((txt[1] - '0') * 10000000u) + 
        ((txt[2] - '0') * 1000000u) + 
        ((txt[3] - '0') * 100000u) + 
        ((txt[4] - '0') * 10000u) + 
        ((txt[5] - '0') * 1000u) + 
        ((txt[6] - '0') * 100u) + 
        ((txt[7] - '0') * 10u) + 
        ((txt[8] - '0') * 1u)
    );
}


u128 math21_cast(char* txt)
{
    /** first block **/
    u128 res = (
        ((txt[0] - '0') * 1000000u) + 
        ((txt[1] - '0') * 100000u) + 
        ((txt[2] - '0') * 10000u) +
        ((txt[3] - '0') * 1000u) + 
        ((txt[4] - '0') * 100u) + 
        ((txt[5] - '0') * 10u) + 
        ((txt[6] - '0') * 1u)
    );

    /** second block **/
    res *= 10000000u;
    res += (
        ((txt[7] - '0') * 1000000u) + 
        ((txt[8] - '0') * 100000u) + 
        ((txt[9] - '0') * 10000u) +
        ((txt[10] - '0') * 1000u) + 
        ((txt[11] - '0') * 100u) + 
        ((txt[12] - '0') * 10u) + 
        ((txt[13] - '0') * 1u)
    );

    /** thirdy block **/
    res *= 10000000u;
    res += (
        ((txt[14] - '0') * 1000000u) + 
        ((txt[15] - '0') * 100000u) + 
        ((txt[16] - '0') * 10000u) +
        ((txt[17] - '0') * 1000u) + 
        ((txt[18] - '0') * 100u) + 
        ((txt[19] - '0') * 10u) + 
        ((txt[20] - '0') * 1u)
    );

    return res;
}

#include <stdio.h>
#include "../libary/str.c"

u128 math_sqrt(u128 n)
{
    f128 guess = 1, absguess = 1, old_guess = 0;

    while (absguess >= 0.001 && old_guess != guess) {
        old_guess = guess;
        guess = ((n/guess) + guess) / 2;
        absguess = (guess * guess) - n;
        absguess = absguess < 0? -absguess: absguess;
    }

    return (f128) guess;
}

b math_cousin(u128 n)
{
    u128 i, npower = math_sqrt(n);
 
    if (n <= 3){
        return false;   
    }

	if (n % 2 == 0 || n % 3 == 0)
		return false;

    for (i = 5;i <= npower; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
	return true;
}

#endif
