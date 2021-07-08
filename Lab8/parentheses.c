/*만약 구조체의 패딩비트를 없애서 딱 5바이트만 사용하고 싶다면*/
/*#pragma pack(1) (== 패딩비트를 1로 만듦) */
/*사용하면 됨. but, 최적의 패빙비트가 4바이트이므로 최적화문제(?)발생 가능 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parentheses.h"

typedef struct {
    char parenthesis;
    int index;
} parentheses_stack_t;

static int set_ascending(const void*, const void*);

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
    const char* str_ptr = str;
    size_t parentheses_count = 0u;
    size_t i = 0u;
    int j = 0;
    size_t str_len = strlen(str);
    parentheses_stack_t** parentheses_stack = (parentheses_stack_t**)malloc(sizeof(parentheses_stack_t*) * str_len);
    parentheses_stack_t** tmp_pp = parentheses_stack;
    
    for (i = 0; i < str_len; i++) {
        *(parentheses_stack + i) = NULL;
    }
    
    i = 0;
    while (*str_ptr != '\0') {
        if (*str_ptr == '(' || *str_ptr == '{' || *str_ptr == '[' || *str_ptr == '<') {
            parentheses_stack[i] = (parentheses_stack_t*)malloc(sizeof(parentheses_stack_t));
            parentheses_stack[i]->parenthesis = *str_ptr;
            parentheses_stack[i++]->index = str_ptr - str;
        }
        
        if (*str_ptr == ')') {
            j = (int)i - 1;
            while (j >= 0) {				
                if (parentheses_stack[j] != NULL && parentheses_stack[j]->parenthesis == '(') {
                    parentheses[parentheses_count].opening_index = parentheses_stack[j]->index;
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
                if (parentheses_stack[j] != NULL && parentheses_stack[j]->parenthesis == *str_ptr - 2) {
                    parentheses[parentheses_count].opening_index = parentheses_stack[j]->index;
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
    
    for (i = 0; i < str_len; i++) {
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
