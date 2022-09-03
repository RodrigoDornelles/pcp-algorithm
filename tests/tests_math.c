#include <assert.h>
#include "../libary/opt.c"
#include "../libary/math.c"

int main(int argc, char** argv)
{
    b fast = has_opt_get(argc, argv, 'f');
    {
        assert(math2_cast("9") == 9);
        assert(math2_cast("09") == 9);
        assert(math2_cast("99") == 99);
    }
    {
        assert(math9_cast("999999999") == 999999999);
    }
    {
        bn big_var1, big_var2;
        big_var1.integer =  999999999999999999llu;
        big_var1.integer = (big_var1.integer * 1000) + 999;
        big_var2.integer = math21_cast("999999999999999999999");
        assert(big_var1.block64[0] == big_var2.block64[0]);
        assert(big_var1.block64[1] == big_var2.block64[1]);
    }
    {
        u128 big_var1 = 28709381510;
        u128 big_var2 = 824228586728903433;
        big_var2 = (big_var2 * 1000) + 113;
        big_var2 = math_sqrt(big_var2);
        assert(big_var1 == big_var2);
    }
    {
        u128 big_var1 = 470529762137600708;
        u128 big_var2 = 999999999999999999;
        big_var1 = (big_var1 * 1000) + 887;
        big_var2 = (big_var2 * 1000) + 999;
        assert(fast? true: math_cousin(big_var1));
        assert(fast? true: !math_cousin(big_var2));
    }

    return 0;
}
