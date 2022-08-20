#ifndef MATH_LIB_PCP_H
#define MATH_LIB_PCP_H

#include "types.c"

int math9_cast(const char* txt)
{
    return (
        ((txt[0] - '0') * 100000000) + 
        ((txt[1] - '0') * 10000000) + 
        ((txt[2] - '0') * 1000000) + 
        ((txt[3] - '0') * 100000) + 
        ((txt[4] - '0') * 10000) + 
        ((txt[5] - '0') * 1000) + 
        ((txt[6] - '0') * 100) + 
        ((txt[7] - '0') * 10) + 
        ((txt[8] - '0') * 1)
    );
}

char math9_cousin(int n)
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
