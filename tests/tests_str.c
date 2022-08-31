#include <assert.h>
#include "../libary/str.c"

int main()
{
    {
        assert(str2_cmp("hi", "hi"));
        assert(!str2_cmp("hi", "hh"));
    }
    {
        assert(str9_cmp("foobarbaz", "foobarbaz"));
        assert(!str9_cmp("foobarbaz", "foobarbax"));
    }
    {
        assert(str21_cmp("foobarbazbee", "foobarbazbee"));
        assert(!str21_cmp("foobarbazbee", "foobarbazbii"));
    }
    {
        char txt[9] = "foobarbaz"; 
        str9_stack(txt, '!');
        assert(str9_cmp("oobarbaz!", txt));
    }
    {
        char txt[21] = "foobarbazbee";
        str21_stack(txt, '!');
        assert(str9_cmp("oobarbazbee!", txt));
    }
    {
        assert(str9_palindrome("foobaboof"));
        assert(!str9_palindrome("foobazoof"));
    }
    {
        assert(str21_palindrome("foobarbazezezabraboof"));
        assert(!str21_palindrome("foobarbazzeezabraboof"));
    }
    {
        char txt[9];
        str9_cast(txt, 999999999);
        assert(str9_cmp("999999999", txt));
    }
    {
        char txt[21];
        i128 big_var = 999999999999999999;
        big_var = (big_var * 1000) + 999;
        str9_cast(txt, big_var);
        assert(str9_cmp("999999999999999999999", txt));
    }
    return 0;
}
