#include <unistd.h>

int main()
{
    char c, size;
    char txt[] = "0x3 ,";
    do {
        size = read(STDIN_FILENO, &txt[3], 1);
        write(STDOUT_FILENO, txt, sizeof(txt) - 1);
    }
    while(size);
   
    return 0;
}