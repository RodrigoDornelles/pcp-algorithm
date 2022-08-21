#include "../libary/str.c"
#include "../libary/opt.c"
#include "../libary/math.c"
#include "../libary/files.c"
#include "../libary/types.c"
#include "../libary/vtable.c"

static const char txt_title[24] = 
    "repeat the palindromes.\n"
;

int main(int argc, char** argv)
{
    fvt func;
    b number;
    u8 exitcode = 0, size = 0;
    char buffer[VT_IDEAL_SIZE] = "";
    b help = has_opt_get(argc, argv, 'h');
    b first = has_opt_get(argc, argv, 'f');
    u8 tier = u8_opt_get(argc, argv, 'T', 1);
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
        /** tier select **/
        if (VT_MIN_TIER > tier || tier > VT_MAX_TIER) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, str_txt_tier, sizeof(str_txt_tier));
            pcp_write(STDERR_FILENO, str_txt_invalid, sizeof(str_txt_invalid));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        } else {
            func = vt_tier(tier);
        }
        /** main loop **/
        while(true) {
            size = pcp_read(filein, buffer, func->size);
            if (size != func->size) {
                break; /** end of file **/
            }
            number = func->str_palindrome(buffer);
            if (number) {
                pcp_write(fileout, buffer, size); /** found it!**/
            }
            if (number && first) {
                break;  /** exit in first time **/
            }
        }
    }   
    while (false);
    return exitcode;    
}
