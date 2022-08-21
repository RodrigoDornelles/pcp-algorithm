#ifndef MATH_LIB_PCP_H
#define MATH_LIB_PCP_H

#include "types.c"

i8 math2_cast(const char* txt)
{
	i8 res = (txt[0] - '0');
	if (txt[1] != '\0') {
		res *= 10;
		res += (txt[1] - '0');
	}
	return res;
}

u64 math9_cast(const char* txt)
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

u64 math21_cast(const char* txt)
{
    return (
        ((txt[0] - '0') * 100000000000000000000u) + 
        ((txt[1] - '0') * 10000000000000000000u) + 
        ((txt[2] - '0') * 1000000000000000000u) +
		((txt[3] - '0') * 100000000000000000u) + 
        ((txt[4] - '0') * 10000000000000000u) + 
        ((txt[5] - '0') * 1000000000000000u) + 
        ((txt[6] - '0') * 100000000000000u) + 
        ((txt[7] - '0') * 10000000000000u) + 
        ((txt[8] - '0') * 1000000000000u) + 
        ((txt[9] - '0') * 100000000000u) + 
        ((txt[10] - '0') * 10000000000u) + 
        ((txt[11] - '0') * 1000000000u) +
        ((txt[12] - '0') * 100000000u) + 
        ((txt[13] - '0') * 10000000u) + 
        ((txt[14] - '0') * 1000000u) + 
        ((txt[15] - '0') * 100000u) + 
        ((txt[16] - '0') * 10000u) + 
        ((txt[17] - '0') * 1000u) + 
        ((txt[18] - '0') * 100u) + 
        ((txt[19] - '0') * 10u) + 
        ((txt[20] - '0') * 1u)
    );
}

char math_cousin(int n)
{
    // Corner cases
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;

	// This is checked so that we can skip
	// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0)
		return false;

	for (int i = 5; i * i <= n; i = i + 6) {
		if (n % i == 0 || n % (i + 2) == 0) {
			return false;
		}
	}

	return true;
}

#endif
