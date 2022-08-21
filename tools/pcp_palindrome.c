#include "../libary/str.c"
#include "../libary/opt.c"
#include "../libary/math.c"
#include "../libary/files.c"
#include "../libary/types.c"

static const char txt_title[37] = 
    "repeat the 9-character palindromes.\n"
;

int main(int argc, char** argv)
{
    b number;
    u8 buffer[10] = "";
    u8 exitcode = 0, size = 0;
    b help = has_opt_get(argc, argv, 'h');
    b first = has_opt_get(argc, argv, 'f');
    u8 offset = u8_opt_get(argc, argv, 'O', 0);
    fn filein = fn_opt_get(argc, argv, 'i', STDIN_FILENO, O_RDONLY);
    fn fileout = fn_opt_get(argc, argv, 'o', STDOUT_FILENO, O_CREAT|O_WRONLY);

    do {
        /** show options **/
        if (help) {
            pcp_write(STDERR_FILENO, txt_title, sizeof(txt_title));
            pcp_write(STDERR_FILENO, str_txt_usage, sizeof(str_txt_usage));
            pcp_write(STDERR_FILENO, str_txt_help, sizeof(str_txt_help));
            break;
        }
        /** open files **/
        if (filein == pcp9_fn_error) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, str_txt_fnnot, sizeof(str_txt_fnnot));
            pcp_write(STDERR_FILENO, str_txt_input, sizeof(str_txt_input));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (fileout == pcp9_fn_error) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, str_txt_fnnot, sizeof(str_txt_fnnot));
            pcp_write(STDERR_FILENO, str_txt_output, sizeof(str_txt_output));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** main loop **/
        while(true) {
            size = pcp_read(filein, buffer, pcp9);
            if (size != pcp9) {
                break; /** end of file **/
            }
            number = str9_palindrome(buffer);
            if (number) {
                pcp_write(fileout, buffer, pcp9); /** found it!**/
            }
            if (number && first) {
                break;  /** exit in first time **/
            }
        }
    }   
    while (false);
    return exitcode;    
}
