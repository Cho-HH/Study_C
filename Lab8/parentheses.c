#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parentheses.h"

static int set_ascending(const void*, const void*);

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
	const char* str_ptr = str;
	size_t parentheses_count = 0u;
	size_t i = 0u;
	int j = 0u;
	int** parentheses_stack = (int**)malloc(sizeof(int*) * max_size);	
	int** tmp_pp = parentheses_stack;

	for (i = 0; i < max_size; i++) {
		*(parentheses_stack + i) = NULL;
	}

	i = 0;
	while (*str_ptr != '\0') {
		if (*str_ptr == '(' || *str_ptr == '{' || *str_ptr == '[' || *str_ptr == '<') {
			parentheses_stack[i] = (int*)malloc(sizeof(int) * 2);
			parentheses_stack[i][0] = *str_ptr;
			parentheses_stack[i++][1] = str_ptr - str;
		}

		if (*str_ptr == ')') {
			j = (int)i - 1;
			while (j >= 0) {				
				if (parentheses_stack[j] != NULL && parentheses_stack[j][0] == '(') {
					parentheses[parentheses_count].opening_index = parentheses_stack[j][1];
					parentheses[parentheses_count++].closing_index = str_ptr - str;
					puts("find and free");
					free(parentheses_stack[j]);
					parentheses_stack[j] = NULL;
					break;
				}
				j--;
			}
		} else if (*str_ptr == '}' || *str_ptr == ']' || *str_ptr == '>') {
			j = (int)i - 1;
			while (j >= 0) {
				if (parentheses_stack[j] != NULL && parentheses_stack[j][0] == *str_ptr - 2) {
					parentheses[parentheses_count].opening_index = parentheses_stack[j][1];
					parentheses[parentheses_count++].closing_index = str_ptr - str;
					puts("find and free");
					free(parentheses_stack[j]);
					parentheses_stack[j] = NULL;
					break;
				}
				j--;
			}
		}

		if (parentheses_count >= max_size) {
			break;
		}

		str_ptr++;
	}

	for (i = 0; i < max_size; i++) {
		if (*(tmp_pp + i) != NULL) {
			free(*(tmp_pp + i));
			*(tmp_pp + i) = NULL;
			puts("free");
		}
	}

	free(tmp_pp);
	puts("free stack");
	printf("parentheses_count : %d\n", parentheses_count);

	qsort(parentheses, parentheses_count, sizeof(parenthesis_t), set_ascending);

	puts("");
	for (i = 0; i < parentheses_count; i++) {
		printf("opening : %d, closing : %d\n", parentheses[i].opening_index, parentheses[i].closing_index);
	}
	puts("");
	puts("");
	return parentheses_count;
}

static int set_ascending(const void* parentheses_1, const void* parentheses_2)
{
	return ((parenthesis_t*)parentheses_1)->opening_index - ((parenthesis_t*)parentheses_2)->opening_index;
}
