#include <assert.h>
#include "../libary/math.c"

int main()
{
    {
        assert(math2_cast("9") == 9);
        assert(math2_cast("09") == 9);
        assert(math2_cast("99") == 99);
    }
    {
        assert(math9_cast("999999999") == 999999999);
    }
    {
        i128 big_var = 999999999999999999;
        big_var = (big_var * 1000) + 999;
        assert(math21_cast("999999999999999999999") == big_var);
    }
    {
        i128 big_var1 = 999999999999999999;
        i128 big_var2 = 989691308101296411;
        big_var1 = (big_var1 * 1000) + 999;
        big_var2 = (big_var2 * 1000) + 113;
        assert(math_cousin(big_var1));
        assert(!math_cousin(big_var2));
    }
}
