#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "tokenize.h"

char** tokenize_malloc(const char* str, const char* delim)
{
	char* str_tmp = NULL;
	char* token = NULL;
	char** token_malloc = NULL;
	char** tmp_malloc = NULL;
	int len = 0;
	size_t i = 0;
	size_t token_count = 0u;

	len = strlen(str);
	str_tmp = (char*)malloc(sizeof(char) * (len + 1));
	strcpy(str_tmp, str);
	str_tmp[len] = '\0';
	printf("%s\n", str_tmp);

	token = strtok(str_tmp, delim);
	token_malloc = (char**)malloc(sizeof(char*));
	while (token != NULL)
	{
		token_count++;
		tmp_malloc = (char**)realloc(token_malloc, sizeof(char*) * (token_count + 1));
		if (tmp_malloc == NULL) {
			goto realloc_fail;
		} else {
			token_malloc = tmp_malloc;
		}

		len = strlen(token);
		token_malloc[i] = (char*)malloc((sizeof(char) * (len + 1)));
		strcpy(token_malloc[i], token);
		token_malloc[i][len] = '\0';
		printf("token : %s\n", token_malloc[i++]);
		token = strtok(NULL, delim);
	}

realloc_fail:
	free(str_tmp);
	token_malloc[i] = NULL;
	return token_malloc;
}

