#include <unistd.h>
#include "../libary/math9.c"

int main()
{
    int size;
    char txt[10];

    do {
        size = read(STDIN_FILENO, txt, sizeof(txt));
        if (str9_is_palindrome(txt)) {
            write(STDOUT_FILENO, txt, sizeof(txt));
        }
    }
    while(size);
}