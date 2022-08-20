#include "../libary/str.c"
#include "../libary/opt.c"
#include "../libary/math.c"
#include "../libary/files.c"
#include "../libary/types.c"
#include "../libary/memory.c"

static const char txt_title[34] =
    "get the 9-character pos.\n"
;

static const char txt_help[] =
    "usage:\n"
    " -h <----------- help\n"
    " -S <----------- search\n"
    " -s01234321 <--- search\n"
    " -ofile1.txt <-- output\n"
    " -ifile2.txt <-- input\n"
;

static const char txt_search[11] = "the search ";
static const char txt_at_pos[8] = "at pos: ";

int main(int argc, char** argv)
{
    i8 c;
    u32 pos = 0;
    u8 search[10];
    u8 buffer[10] = "";
    u8 exitcode = 0, size = 0;
    b help = has_opt_get(argc, argv, 'h');
    b find_stdin = has_opt_get(argc, argv, 'S');
    u8 find_file = txt_opt_get(argc, argv, 's', search);
    u8 offset = u8_opt_get(argc, argv, 'O', 0);
    fn filein = fn_opt_get(argc, argv, 'i', STDIN_FILENO, O_RDONLY);
    fn fileout = fn_opt_get(argc, argv, 'o', STDOUT_FILENO, O_CREAT|O_WRONLY);

    do {
        /** show options **/
        if (help) {
            pcp_write(STDERR_FILENO, txt_title, sizeof(txt_title));
            pcp_write(STDERR_FILENO, txt_help, sizeof(txt_help));
            break;
        }
        /** open files **/
        if (filein == pcp9_fn_error) {
            pcp_write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            pcp_write(STDERR_FILENO, str9_txt_fnnot, sizeof(str9_txt_fnnot));
            pcp_write(STDERR_FILENO, str9_txt_input, sizeof(str9_txt_input));
            pcp_write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        if (fileout == pcp9_fn_error) {
            pcp_write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            pcp_write(STDERR_FILENO, str9_txt_fnnot, sizeof(str9_txt_fnnot));
            pcp_write(STDERR_FILENO, str9_txt_output, sizeof(str9_txt_output));
            pcp_write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** verify search **/
        if (find_stdin && !find_file){
            find_file = pcp_read(STDIN_FILENO, search, pcp9);
        }
        if (find_file != pcp9) {
            pcp_write(STDERR_FILENO, str9_txt_error, sizeof(str9_txt_error));
            pcp_write(STDERR_FILENO, txt_search, sizeof(txt_search));
            pcp_write(STDERR_FILENO, str9_txt_invalid, sizeof(str9_txt_invalid));
            pcp_write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** main loop **/
        while(++pos) {
            /** first time **/
            if (buffer[0] == '\0') {
                size = pcp_read(filein, buffer, pcp9);
                if (size != pcp9) {
                    break; /** small file **/
                }
            }
            /** each time **/
            else {
                size = pcp_read(filein, &c, 1);
                if (size == 0) {
                    break; /** end of file **/
                }
                str9_stack(buffer, c);                
            }
            if (str9_cmp(search, buffer) == true) {
                str9_cast(search, pos);
                pcp_write(fileout, buffer, pcp9);
                pcp_write(STDERR_FILENO, txt_at_pos, sizeof(txt_at_pos));
                pcp_write(STDERR_FILENO, search, pcp9);
                pcp_write(STDERR_FILENO, str9_txt_end_dot, sizeof(str9_txt_end_dot));
                break;
            }            
        }
    }   
    while (false);
    return exitcode;    
}
