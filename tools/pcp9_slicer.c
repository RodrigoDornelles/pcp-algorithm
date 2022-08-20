#include <unistd.h>
#include <fcntl.h>
#include "../libary/str9.c"
#include "../libary/opt9.c"
#include "../libary/types9.c"

static const char txt_title[52] = 
    "slicer 9-character, with offset and header removal.\n"
;
static const char txt_help[] =
    "usage:\n"
    " -h <----------- help\n"
    " -H <----------- rm 3.\n"
    " -t <----------- trash\n"
    " -O0 <---------- offset\n"
    " -ofile1.txt <-- output\n"
    " -ifile2.txt <-- input\n"
;
static const char txt_fn_errorf[] = "the offset ";
static const char txt_fn_errorh[] = "the header ";
static const char txt_fn_errorg[] = "is greater than the ";
static const char txt_trash[] = "trash:\n \"";

u8 main(u8 argc, s* argv)
{
    u8 buffer[10] = "";
    u8 exitcode = 0, size = 0;
    b help = has_opt9_get(argc, argv, 'h');
    b trash = has_opt9_get(argc, argv, 't');
    b header = has_opt9_get(argc, argv, 'H');
    u8 offset = u8_opt9_get(argc, argv, 'O', 0);
    fn filein = fn_opt9_get(argc, argv, 'i', STDIN_FILENO, O_RDONLY);
    fn fileout = fn_opt9_get(argc, argv, 'o', STDOUT_FILENO, O_CREAT|O_WRONLY);

    do {
        /** show options **/
        if (help) {
            write(STDERR_FILENO, txt_title, sizeof(txt_title));
            write(STDERR_FILENO, txt_help, sizeof(txt_help));
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
        /** header remove **/
        if (header) {
            size = read(filein, buffer, str9_h2);
        }
        if (header && size < str9_h2) {
            write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            write(STDERR_FILENO, txt_fn_errorh, sizeof(txt_fn_errorh) - 1);
            write(STDERR_FILENO, txt_fn_errorg, sizeof(txt_fn_errorg));
            write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (header && str2_cmp(buffer, str9_header) == false) {
            write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            write(STDERR_FILENO, txt_fn_errorh, sizeof(txt_fn_errorh) - 1);
            write(STDERR_FILENO, str9_txt_invalid, sizeof(str9_txt_invalid));
            write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** offset remove **/
        if (offset > 0) {
            size = read(filein, buffer, offset);
        }
        if (offset && size < offset) {
            write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            write(STDERR_FILENO, txt_fn_errorf, sizeof(txt_fn_errorf) - 1);
            write(STDERR_FILENO, txt_fn_errorg, sizeof(txt_fn_errorg));
            write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (offset && trash) {
            write(STDERR_FILENO, buffer, offset);
            break;
        }
        if (offset == 0 && trash) {
            write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            write(STDERR_FILENO, txt_fn_errorf, sizeof(txt_fn_errorf) - 1);
            write(STDERR_FILENO, str9_txt_invalid, sizeof(str9_txt_invalid));
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
            write(fileout, buffer, pcp9);
        }
    }
    while (false);
    return exitcode;
}