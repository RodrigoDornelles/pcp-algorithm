#include <unistd.h>
#include <fcntl.h>
#include "../libary/str9.c"
#include "../libary/opt9.c"
#include "../libary/math9.c"
#include "../libary/types9.c"

static const char txt_title[34] =
    "repeat the 9-digit prime numbers.\n"
;

int main(u8 argc, s* argv)
{
    u32 number;
    u8 buffer[10] = "";
    u8 exitcode = 0, size = 0;
    b help = has_opt9_get(argc, argv, 'h');
    b first = has_opt9_get(argc, argv, 'f');
    u8 offset = u8_opt9_get(argc, argv, 'O', 0);
    fn filein = fn_opt9_get(argc, argv, 'i', STDIN_FILENO, O_RDONLY);
    fn fileout = fn_opt9_get(argc, argv, 'o', STDOUT_FILENO, O_CREAT|O_WRONLY);

    do {
        /** show options **/
        if (help) {
            write(STDERR_FILENO, txt_title, sizeof(txt_title));
            write(STDERR_FILENO, str9_txt_help, sizeof(str9_txt_help));
            break;
        }
        /** open files **/
        if (filein == pcp9_fn_error) {
            write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            write(STDERR_FILENO, str9_txt_fnnot, sizeof(str9_txt_fnnot));
            write(STDERR_FILENO, str9_txt_input, sizeof(str9_txt_input));
            write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (fileout == pcp9_fn_error) {
            write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            write(STDERR_FILENO, str9_txt_fnnot, sizeof(str9_txt_fnnot));
            write(STDERR_FILENO, str9_txt_output, sizeof(str9_txt_output));
            write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** main loop **/
        while(true) {
            size = read(filein, buffer, pcp9);
            if (size != pcp9) {
                break; /** end of file **/
            }
            number = math9_cast(buffer);
            number = math9_cousin(number);
            if (number) {
                write(fileout, buffer, pcp9); /** found it!**/
            }
            if (number && first) {
                break;  /** exit in first time **/
            }
        }
    }   
    while (false);
    return exitcode;    
}
