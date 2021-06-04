#include <stdio.h>
#include <string.h>
#include "translate.h"

#define MAX_BUFFER (512)
#define TRUE (1)
#define FALSE (0)

int escape_check(char str[])
{
    char* escape_checker = str;
    char* i = NULL;
    
    while (*escape_checker != '\0') {
        if (*escape_checker == 0x5c) {
            switch (*(escape_checker + 1)) {
            case 0x5c: /* '\' */
                *escape_checker = '\\';
                break;
            case 'a':
                *escape_checker = '\a';
                break;
            case 'b':
                *escape_checker = '\b';
                break;
            case 'f':
                *escape_checker = '\f';
                break;
            case 'n':
                *escape_checker = '\n';
                break;
            case 'r':
                *escape_checker = '\r';
                break;
            case 't':
                *escape_checker = '\t';
                break;
            case 'v':
                *escape_checker = '\v';
                break;
            case 0x27: /* ''' */
                *escape_checker = '\'';
                break;
            case '"':
                *escape_checker = '\"';
                break;
            default:
                return 1;
                break;
            }
            
            for (i = escape_checker + 1; *i != '\0'; i++) {
                *i = *(i + 1);
            } 
        }		
        escape_checker++;
    }
    return 0;
}

int range(char str[])
{
    char* check_first_range = str;
    char* check_range_mark = str + 1;
    char* check_last_range = str + 2;
    char* save_range_mark = NULL;
    char* save_last_range = NULL;
    char* save_first_range = NULL;
    int range = 0;
    int i = 0;
    char* tmp = NULL;
    char* tmp2 = NULL;
    int str_len = 0;
    
    while (*check_last_range != '\0' && *check_first_range != '\0') {
        if (*check_range_mark == '-') {			
            if (*check_last_range - *check_first_range < 0) {
                return 1;
            } else if (*check_last_range - *check_first_range == 0) {
                save_first_range = check_first_range;
                save_last_range = check_last_range;
                while (*save_last_range != '\0') {
                    *save_first_range = *save_last_range;
                    save_first_range++;
                    save_last_range++;
                }
                *(save_last_range - 2) = '\0';
            } else if (*check_last_range - *check_first_range == 1) {
                save_first_range = check_range_mark;
                save_last_range = check_last_range;
                while (*save_last_range != '\0') {
                    *save_first_range = *save_last_range;
                    save_first_range++;
                    save_last_range++;
                }
                *(save_last_range - 1) = '\0';
                check_first_range++;
                check_range_mark++;
                check_last_range++;
            } else if (*check_last_range - *check_first_range == 2) {
                *check_range_mark = *check_first_range + 1;
                check_first_range += 2;
                check_range_mark += 2;
                check_last_range += 2;
            } else { 
                str_len = strlen(str);
                range = *check_last_range - *check_first_range - 2;
                if (str_len + range >= MAX_BUFFER) {
                    return 2;
                }		
				
                /*a-d에서 d의 주소*/
                save_first_range = check_last_range;
                /*abcd에서 d의주소*/
                save_last_range = check_last_range + range;
                tmp = save_last_range;
                tmp2 = str + str_len + range + 1;
                while (tmp2 != save_last_range - 1) {
                    *tmp2 = *(tmp2 - range);
                    tmp2--;
                }
                save_range_mark = check_range_mark;
                for (i = 1; i <= range + 1; i++) {
                    *save_range_mark = (*check_first_range) + i;
                    save_range_mark++;
                }
                check_first_range = tmp;
                check_range_mark = check_first_range + 1;
                check_last_range = check_first_range + 2;
				
            }		
        } 
		
        check_first_range++;
        check_range_mark++;
        check_last_range++;
    }
    
    
    return 0;
}

int translate_buffer(const char** argv, size_t argv1_num, size_t argv2_num, size_t is_flag) 
{
    size_t error = 0u;
    char argv1_buffer[MAX_BUFFER] = { 0, };
    char argv2_buffer[MAX_BUFFER] = { 0, };
    int argv1_len = 0;
    int argv2_len = 0;
    int i = 0;
    int j = 0;
    char save_char = 0;
	
    if (strlen(argv[argv1_num]) >= MAX_BUFFER || strlen(argv[argv2_num]) >= MAX_BUFFER) {
        return ERROR_CODE_ARGUMENT_TOO_LONG;
    }
	
    strncpy(argv1_buffer, argv[argv1_num], MAX_BUFFER);
    argv1_buffer[MAX_BUFFER - 1] = '\0';		
    error = escape_check(argv1_buffer);
    if (error == 1) {
        return ERROR_CODE_INVALID_FORMAT;
    }
    argv1_len = strlen(argv1_buffer);
    if (argv1_len >= 3) {
        error = range(argv1_buffer);
        if (error == 1) {
            return ERROR_CODE_INVALID_RANGE;
        } else if (error == 2) {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
    }
    argv1_len = strlen(argv1_buffer);
	
    strncpy(argv2_buffer, argv[argv2_num], MAX_BUFFER); 
    argv2_buffer[MAX_BUFFER - 1] = '\0';
    error = escape_check(argv2_buffer);
    if (error == 1) {
        return ERROR_CODE_INVALID_FORMAT;
    }
    argv2_len = strlen(argv2_buffer);
    if (argv2_len >= 3) {
        error = range(argv2_buffer);
        if (error == 1) {
            return ERROR_CODE_INVALID_RANGE;
        } else if (error == 2) {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
    }
    argv2_len = strlen(argv2_buffer);
	
    if (argv1_len > argv2_len) {
        for (i = argv2_len; i < argv1_len; i++) {
            argv2_buffer[i] = argv2_buffer[argv2_len - 1];
        }
    }
    argv2_buffer[argv1_len] = '\0';			
	
    for (i = argv1_len - 1; i >= 0; i--) {
        save_char = argv1_buffer[i];
        for (j = i - 1; j >= 0; j--) {
            if (save_char == argv1_buffer[j]) {				
                argv1_buffer[j] = ' ';
                argv2_buffer[j] = ' ';
            }
        }
    }

    /*printf("argv1_buffer : %s, argv1_buffer_length : %d\n", argv1_buffer, argv1_len);
    printf("argv2_buffer : %s\n", argv2_buffer);*/
    if (is_flag == FALSE) {
        while (1) {
            j = getchar();
            if (j == EOF) {
                break;
            }
            for (i = 0; *(argv1_buffer + i) != '\0'; i++) {		
                if (j == *(argv1_buffer + i)) {
                    j = *(argv2_buffer + i);
                    break;
                }
            }
            putchar(j);
        }
    } else if (is_flag == TRUE) {
        while (1) {
            j = getchar();
            if (j == EOF) {
                break;
            }
            for (i = 0; *(argv1_buffer + i) != '\0'; i++) { 				
                if (j == *(argv1_buffer + i) || j == (*(argv1_buffer + i) ^ 0x20)) {
                    j = *(argv2_buffer + i);
                    break;
                }
            }
            putchar(j);
        }
    }
    
    return 0;
}

int translate(int argc, const char** argv)
{	
    if (argc == 3) {
        return translate_buffer(argv, 1, 2, FALSE);
    } else if (argc == 4) {		
        if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0') {
            return translate_buffer(argv, 2, 3, TRUE);
        } else {
            return ERROR_CODE_INVALID_FLAG;
        }
    } else {
        return ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
    }
}
