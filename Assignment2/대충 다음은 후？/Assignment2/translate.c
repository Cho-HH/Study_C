#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "translate.h"

int escape_check_buffer(int* argv_len, char argv_buffer[], const char** argv, size_t argv_num);
void check_argv1_len(int argv1_len, int argv2_len, char argv2_buffer[]);
void translate_result(char argv1_buffer[], char argv2_buffer[], size_t is_flag);

enum {
	MAX_BUFFER = 512
};

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
    int error = 0;
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
	
	error = escape_check_buffer(&argv1_len, argv1_buffer, argv, argv1_num);
	if (error != 0) {
		return error;
	} 

	error = escape_check_buffer(&argv2_len, argv2_buffer, argv, argv2_num);
	if (error != 0) {
		return error;
	} 
	
	check_argv1_len(argv1_len, argv2_len, argv2_buffer);
   
    for (i = argv1_len - 1; i >= 0; i--) {
        save_char = argv1_buffer[i];
        for (j = i - 1; j >= 0; j--) {
            if (save_char == argv1_buffer[j]) {				
                argv1_buffer[j] = ' ';
                argv2_buffer[j] = ' ';
            }
        }
    }

    printf("argv1_buffer : %s\n", argv1_buffer);
    printf("argv2_buffer : %s\n", argv2_buffer);
	
	translate_result(argv1_buffer, argv2_buffer, is_flag);
    
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

int escape_check_buffer (int* argv_len, char argv_buffer[], const char** argv, size_t argv_num) 
{
	/*escape문자를 확인하고 난 뒤의 buffer*/
	int error = 0;
	
	strncpy(argv_buffer, argv[argv_num], MAX_BUFFER);
    argv_buffer[MAX_BUFFER - 1] = '\0';		
    error = escape_check(argv_buffer);
    if (error == 1) {
        return ERROR_CODE_INVALID_FORMAT;
    }
    *argv_len = strlen(argv_buffer);
    if (*argv_len >= 3) {
        error = range(argv_buffer);
        if (error == 1) {
            return ERROR_CODE_INVALID_RANGE;
        } else if (error == 2) {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
    }
    *argv_len = strlen(argv_buffer);
	return 0;
}	

void check_argv1_len(int argv1_len, int argv2_len, char argv2_buffer[])
{
	int i = 0;
	
	if (argv1_len > argv2_len) {
        for (i = argv2_len; i < argv1_len; i++) {
            argv2_buffer[i] = argv2_buffer[argv2_len - 1];
        }
    }
    argv2_buffer[argv1_len] = '\0';			
}

void translate_result(char argv1_buffer[], char argv2_buffer[], size_t is_flag)
{
	int i = 0;
	int j = 0;
	
    while (1) {
        j = getchar();
        if (j == EOF) {
            break;
        }
        for (i = 0; *(argv1_buffer + i) != '\0'; i++) {
			if (is_flag == TRUE) {
				if (j == *(argv1_buffer + i) || j == (*(argv1_buffer + i) ^ 0x20)) {
					j = *(argv2_buffer + i);
					break;
				}
			} else  {
				if (j == *(argv1_buffer + i)) {
					j = *(argv2_buffer + i);
					break;
				}
			}
        }
        putchar(j);
    }
}
