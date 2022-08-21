#include "../libary/str.c"
#include "../libary/opt.c"
#include "../libary/files.c"
#include "../libary/types.c"

static const char txt_title[52] = 
    "slicer 9-character, with offset and header removal.\n"
;
static const char txt_help[] =
    "-H <--------- rm header\n "
    "-t <--------- show trash\n "
    "-O0 <-------- select offset\n "
;
static const char txt_fn_errorf[] = "the offset ";
static const char txt_fn_errorh[] = "the header ";
static const char txt_fn_errorg[] = "is greater than the ";
static const char txt_trash[] = "trash:\n \"";

int main(int argc, char** argv)
{
    u8 buffer[10] = "";
    u8 exitcode = 0, size = 0;
    b help = has_opt_get(argc, argv, 'h');
    b trash = has_opt_get(argc, argv, 't');
    b first = has_opt_get(argc, argv, 'f');
    b header = has_opt_get(argc, argv, 'H');
    u8 tier = u8_opt_get(argc, argv, 'T', 1);
    u8 offset = u8_opt_get(argc, argv, 'O', 0);
    fn filein = fn_opt_get(argc, argv, 'i', STDIN_FILENO, O_RDONLY);
    fn fileout = fn_opt_get(argc, argv, 'o', STDOUT_FILENO, O_CREAT|O_WRONLY);

    do {
        /** show options **/
        if (help) {
            pcp_write(STDERR_FILENO, txt_title, sizeof(txt_title));
            pcp_write(STDERR_FILENO, str_txt_usage, sizeof(str_txt_usage));
            pcp_write(STDERR_FILENO, txt_help, sizeof(txt_help));
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
        if (1 > tier || tier > 3) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, str_txt_tier, sizeof(str_txt_tier));
            pcp_write(STDERR_FILENO, str_txt_invalid, sizeof(str_txt_invalid));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** header remove **/
        if (header) {
            size = pcp_read(filein, buffer, str9_h2);
        }
        if (header && size < str9_h2) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, txt_fn_errorh, sizeof(txt_fn_errorh) - 1);
            pcp_write(STDERR_FILENO, txt_fn_errorg, sizeof(txt_fn_errorg));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (header && str2_cmp(buffer, str9_header) == false) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, txt_fn_errorh, sizeof(txt_fn_errorh) - 1);
            pcp_write(STDERR_FILENO, str_txt_invalid, sizeof(str_txt_invalid));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** offset remove **/
        if (offset > 0) {
            size = pcp_read(filein, buffer, offset);
        }
        if (offset && size < offset) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, txt_fn_errorf, sizeof(txt_fn_errorf) - 1);
            pcp_write(STDERR_FILENO, txt_fn_errorg, sizeof(txt_fn_errorg));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (offset && trash) {
            pcp_write(STDERR_FILENO, buffer, offset);
            break;
        }
        if (offset == 0 && trash) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, txt_fn_errorf, sizeof(txt_fn_errorf) - 1);
            pcp_write(STDERR_FILENO, str_txt_invalid, sizeof(str_txt_invalid));
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
            pcp_write(fileout, buffer, pcp9);
            if (first) {
                break;
            }
        }
    }
    while (false);
    return exitcode;
}