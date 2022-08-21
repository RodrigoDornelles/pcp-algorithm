#include "../libary/str.c"
#include "../libary/opt.c"
#include "../libary/math.c"
#include "../libary/files.c"
#include "../libary/types.c"
#include "../libary/vtable.c"


static const char txt_title[18] =
    "get the term pos.\n"
;

static const char txt_help[] =
    "-S <--------- search stdin\n "
    "-s000... <--- search term\n "
;

static const char txt_search[11] = "the search ";
static const char txt_at_pos[8] = "at pos: ";

int main(int argc, char** argv)
{
    i8 c;
    fvt func;
    u64 pos = 0;
    u8 exitcode = 0, size = 0;
    u8 search[VT_IDEAL_SIZE];
    u8 buffer[VT_IDEAL_SIZE] = "";
    u8 buffer2[VT_IDEAL_SIZE] = "";
    b help = has_opt_get(argc, argv, 'h');
    b first = has_opt_get(argc, argv, 'f');
    b find_stdin = has_opt_get(argc, argv, 'S');
    u8 tier = u8_opt_get(argc, argv, 't', 1);
    u8 find_file = txt_opt_get(argc, argv, 's', search);
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
        /** verify search **/
        if (find_stdin && !find_file){
            find_file = pcp_read(STDIN_FILENO, search, func->size);
        }
        if (find_file != func->size) {
            pcp_write(STDERR_FILENO, str_txt_error, sizeof(str_txt_error));
            pcp_write(STDERR_FILENO, txt_search, sizeof(txt_search));
            pcp_write(STDERR_FILENO, str_txt_invalid, sizeof(str_txt_invalid));
            pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
            exitcode = pcp9_exit_error;
            break;
        }
        /** main loop **/
        while(++pos) {
            /** first time **/
            if (buffer[0] == '\0') {
                size = pcp_read(filein, buffer, func->size);
                if (size != func->size) {
                    break; /** small file **/
                }
            }
            /** each time **/
            else {
                size = pcp_read(filein, &c, 1);
                if (size == 0) {
                    break; /** end of file **/
                }
                func->str_stack(buffer, c);                
            }
            if (str9_cmp(search, buffer) == true) {
                func->str_from_int(buffer2, pos);
                pcp_write(fileout, buffer, func->size);
                pcp_write(STDERR_FILENO, txt_at_pos, sizeof(txt_at_pos));
                pcp_write(STDERR_FILENO, buffer2, func->size);
                pcp_write(STDERR_FILENO, str_txt_end_dot, sizeof(str_txt_end_dot));
                if (first) {
                    break;
                }
            }            
        }
    }   
    while (false);
    return exitcode;    
}
