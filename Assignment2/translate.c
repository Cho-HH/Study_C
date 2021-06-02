#include <stdio.h>
#include <string.h>
#include "translate.h"

#define MAX_BUFFER (512)

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

int translate(int argc, const char** argv)
{	
    size_t error = 0u;
    char str[MAX_BUFFER] = { 0, };
    char argv1_buffer[MAX_BUFFER] = { 0, };
    char argv2_buffer[MAX_BUFFER] = { 0, };
    int argv1_len = 0;
    int argv2_len = 0;
    int i = 0;
    int j = 0;
    char save_char = 0;
    
    
    
    if (argc == 3) {
        if (strlen(argv[1]) > MAX_BUFFER || strlen(argv[2]) > MAX_BUFFER) {
            printf("ERROR_CODE_ARGUMENT_TOO_LONG");
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
        
        strncpy(argv1_buffer, argv[1], MAX_BUFFER);
        argv1_buffer[MAX_BUFFER - 1] = '\0';		
        error = escape_check(argv1_buffer);
        if (error == 1) {
            printf("ERROR_CODE_INVALID_FORMAT");
            return ERROR_CODE_INVALID_FORMAT;
        }
        
        argv1_len = strlen(argv1_buffer);
        
        strncpy(argv2_buffer, argv[2], argv1_len);
        argv2_buffer[argv1_len] = '\0';			
        error = escape_check(argv2_buffer);
        if (error == 1) {
            printf("ERROR_CODE_INVALID_FORMAT");
            return ERROR_CODE_INVALID_FORMAT;
        }
        argv2_len = strlen(argv2_buffer);
        
        /*printf("first argv1_len : %d\n", argv1_len);
        printf("first argv2_len : %d\n", argv2_len);*/
        
        if (argv1_len > argv2_len) {
            for (i = argv2_len; i < argv1_len; i++) {
                argv2_buffer[i] = argv2_buffer[argv2_len - 1];
            }
        }
        
        for (i = argv1_len - 1; i >= 0; i--) {
            save_char = argv1_buffer[i];
            for (j = i - 1; j >= 0; j--) {
                if (save_char == argv1_buffer[j]) {				
                    argv1_buffer[j] = ' ';
                    argv2_buffer[j] = ' ';
                }
            }
        }
        
        /*printf("argv1 : %s, argv1_len : %d\n", argv1_buffer, strlen(argv1_buffer));
        printf("argv2 : %s, argv2_len : %d\n", argv2_buffer, strlen(argv2_buffer));*/
        while (1) {
            j = getchar();
            if (j == EOF) {
                break;
            }
            for (i = 0; *(argv1_buffer + i) != '\0'; i++) { /*argv[1][i]*/				
                if (j == *(argv1_buffer + i)) {
                    j = *(argv2_buffer + i);
                    break;
                }
            }
            putchar(j);
        }
    } else if (argc == 4) {		
        if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0') {
            if (strlen(argv[2]) > MAX_BUFFER || strlen(argv[3]) > MAX_BUFFER) {
                printf("ERROR_CODE_ARGUMENT_TOO_LONG");
                return ERROR_CODE_ARGUMENT_TOO_LONG;
            }
            
            strncpy(argv1_buffer, argv[2], MAX_BUFFER);
            argv1_buffer[MAX_BUFFER - 1] = '\0';		
            error = escape_check(argv1_buffer);
            if (error == 1) {
                printf("ERROR_CODE_INVALID_FORMAT");
                return ERROR_CODE_INVALID_FORMAT;
            }
            
            argv1_len = strlen(argv1_buffer);
            
            strncpy(argv2_buffer, argv[3], argv1_len);
            argv2_buffer[argv1_len] = '\0';			
            error = escape_check(argv2_buffer);
            if (error == 1) {
                printf("ERROR_CODE_INVALID_FORMAT");
                return ERROR_CODE_INVALID_FORMAT;
            }
            argv2_len = strlen(argv2_buffer);
            
            /*printf("first argv1_len : %d\n", argv1_len);
            printf("first argv2_len : %d\n", argv2_len);*/
            
            if (argv1_len > argv2_len) {
                for (i = argv2_len; i < argv1_len; i++) {
                    argv2_buffer[i] = argv2_buffer[argv2_len - 1];
                }
            }
            
            for (i = argv1_len - 1; i >= 0; i--) {
                save_char = argv1_buffer[i];
                for (j = i - 1; j >= 0; j--) {
                    if (save_char == argv1_buffer[j]) {				
                        argv1_buffer[j] = ' ';
                        argv2_buffer[j] = ' ';
                    }
                }
            }
            
            /*printf("argv1 : %s, argv1_len : %d\n", argv1_buffer, strlen(argv1_buffer));
            printf("argv2 : %s, argv2_len : %d\n", argv2_buffer, strlen(argv2_buffer));*/
            
            while (1) {
                j = getchar();
                if (j == EOF) {
                    break;
                }
                for (i = 0; *(argv1_buffer + i) != '\0'; i++) { /*argv[1][i]*/				
                    if (j == *(argv1_buffer + i) || j == (*(argv1_buffer + i) ^ 0x20)) {
                        j = *(argv2_buffer + i);
                        break;
                    }
                }
                putchar(j);
            }
        } else {
            printf("ERROR_CODE_INVALID_FLAG");
            return ERROR_CODE_INVALID_FLAG;
        }
    } else {
        printf("ERROR_CODE_WRONG_ARGUMENTS_NUMBER");
        return ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
    }
    
    printf("%s\n", str);
    return 0;
}
