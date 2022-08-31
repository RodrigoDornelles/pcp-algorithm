#include <assert.h>
#include <string.h>
#include "../libary/opt.c"

int main()
{
    {
        char *argv[] = {"-g99"};
        char argc = 1;
        assert(u8_opt_get(argc, argv, 'g', 44) == 99);
        assert(u8_opt_get(argc, argv, 'G', 44) == 44);
    }
    {
        char *argv[] = {"-h"};
        char argc = 1;
        assert(has_opt_get(argc, argv, 'h'));
        assert(!has_opt_get(argc, argv, 'H'));
    }
    {
        char txt[4];
        char *argv[] = {"-Zfoo"};
        char argc = 1;
        assert(txt_opt_get(argc, argv, 'Z', txt));
        assert(strcmp("foo", txt) == 0);
    }
    return 0;
}