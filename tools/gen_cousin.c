#include <unistd.h>
#include "../libary/math9.c"
#include "../lockuptables/pi_ascii.c"

int main()
{
    int i, number, offset;

    for (offset = 0; offset < 9; offset += 1) {
        for (i = 0; i < sizeof(pi_ascii)/9; i += 9) {
            number = str9_to_int(&pi_ascii[i+offset]);
            if (is_cousin_fast(number)) {
                write(STDOUT_FILENO, &pi_ascii[i+offset], 9);
                write(STDOUT_FILENO, "\n", 1);
            }
        }
    }
}
