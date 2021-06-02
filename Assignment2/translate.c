#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "translate.h"

#define MAX_BUFFER (512)

/*void translate_buffer (*/
int translate(int argc, const char** argv)
{	
	char str[MAX_BUFFER] = { 0, };
	char argv1_buffer[MAX_BUFFER] = { 0, };
	char argv2_buffer[MAX_BUFFER] = { 0, };
	char* check_str = NULL;
	int argv1_len = 0;
	int argv2_len = 0;
	int i = 0;
	int j = 0;
	char save_char = 0;
	
	
	
	if (argc == 3) {
		argv1_len = strlen(argv[1]);
		argv2_len = strlen(argv[2]);
		
		if (argv1_len > MAX_BUFFER || argv2_len > MAX_BUFFER) {
			return ERROR_CODE_ARGUMENT_TOO_LONG;
		}
		
		strncpy(argv1_buffer, argv[1], MAX_BUFFER);
		argv1_buffer[MAX_BUFFER - 1] = '\0';
		strncpy(argv2_buffer, argv[2], argv1_len);
		argv2_buffer[argv1_len] = '\0';
		
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
		
		printf("argv1 : %s\n",argv1_buffer);
		printf("argv2 : %s\n",argv2_buffer);
		
		if (fgets(str, MAX_BUFFER, stdin) != NULL) {
			for (check_str = str; *check_str != '\0'; check_str++) {
				for (i = 0; *(argv1_buffer + i) != '\0'; i++) { /*argv[1][i]*/				
					if (*check_str == *(argv1_buffer + i)) {
						*check_str = *(argv2_buffer + i);
					}
				}
			}			
		} 
		
		
	} else if (argc == 4) {		
		if (argv[1][0] == '-' && argv[1][1] == 'i' && argv[1][2] == '\0') {
			argv1_len = strlen(argv[2]);
			argv2_len = strlen(argv[3]);
			
			strncpy(argv1_buffer, argv[2], MAX_BUFFER);
			argv1_buffer[MAX_BUFFER - 1] = '\0';
			strncpy(argv2_buffer, argv[3], argv1_len);
			argv2_buffer[argv1_len] = '\0';
			
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
			
			/*printf("argv1 : %s\n",argv1_buffer);
			printf("argv2 : %s\n",argv2_buffer);	*/				
			
			if (fgets(str, MAX_BUFFER, stdin) != NULL) {
				for (check_str = str; *check_str != '\0'; check_str++) {
					for (i = 0; *(argv1_buffer + i) != '\0'; i++) { /*argv[1][i]*/				
						if (*check_str == *(argv1_buffer + i) || *check_str == (*(argv1_buffer + i) ^ 0x20)) {
							*check_str = *(argv2_buffer + i);
						}
					}
				}			
			} 
		}
	}

	/*printf("%s", str);*/
	return 0;
}
