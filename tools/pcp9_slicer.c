#include <unistd.h>
#include <fcntl.h>
#include "../libary/types.c"
#include "../libary/opt.c"

static const char txt_help[] =
    "usage:\n"
    " -h <----------- help\n"
    " -t <----------- trash\n"
    " -O0 <---------- offset\n"
    " -ofile1.txt <-- output\n"
    " -ifile2.txt <-- input\n"
;
static const char txt_fn_errorof[] = 
    "offset is greater than"
    "the input file.\n"
;
static const char txt_error[] = "error:\n ";
static const char txt_fn_error[] = "could not open ";
static const char txt_fn_errori[] = "input file.\n";
static const char txt_fn_erroro[] = "output file.\n";
static const char txt_trash1[] = "trash:\n \"";
static const char txt_trash2[] = "\"\n";

u8 main(u8 argc, i8** argv)
{
    u8 buffer[10] = "";
    u8 exitcode = 0, size = 0;
    b help = has_opt_get(argc, argv, 'h');              
    b trash = has_opt_get(argc, argv, 't');              
    u8 offset = u8_opt_get(argc, argv, 'O', 0);            
    fn filein = fn_opt_get(argc, argv, 'i', STDIN_FILENO, O_RDONLY);
    fn fileout = fn_opt_get(argc, argv, 'o', STDOUT_FILENO, O_CREAT | O_WRONLY);

    do {
        /** options **/
        if (help) {
            write(STDERR_FILENO, txt_help, sizeof(txt_help));
            break;
        }
        if (filein == fnerror) {
            write(STDERR_FILENO, txt_error, sizeof(txt_error) - 1);
            write(STDERR_FILENO, txt_fn_error, sizeof(txt_fn_error) - 1);
            write(STDERR_FILENO, txt_fn_errori, sizeof(txt_fn_errori));
            exitcode = 15;
            break;
        }
        if (fileout == fnerror) {
            write(STDERR_FILENO, txt_error, sizeof(txt_error) - 1);
            write(STDERR_FILENO, txt_fn_error, sizeof(txt_fn_error) - 1);
            write(STDERR_FILENO, txt_fn_erroro, sizeof(txt_fn_erroro));
            exitcode = 15;
            break;
        }
        if (offset > 0) {
            size = read(filein, buffer, offset);
        }
        if (size < offset) {
            write(STDERR_FILENO, txt_error, sizeof(txt_error) - 1);
            write(STDERR_FILENO, txt_fn_errorof, sizeof(txt_fn_errorof));
            exitcode = 15;
            break;
        }
        if (trash) {
            write(STDERR_FILENO, txt_trash1, sizeof(txt_trash1) - 1);
            write(STDERR_FILENO, buffer, sizeof(buffer));
            write(STDERR_FILENO, txt_trash2, sizeof(txt_trash2));
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