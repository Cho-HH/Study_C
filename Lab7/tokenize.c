/*#define _CRT_SECURE_NO_WARNINGS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

static size_t get_word_count(const char* str, const char* delim);
static void get_array(const char* str, const char* delim, char** words);

char** tokenize_malloc(const char* str, const char* delim)
{
    char** word_array = NULL;
    size_t word_count = 0u;
    /*size_t j = 0u;*/
    
    word_count = get_word_count(str, delim);
    
    /*printf("word_count : %d\n", word_count);*/
    
    word_array = (char**)malloc(sizeof(char*) * word_count + 1);
    
    get_array(str, delim, word_array);
    
    /*for (j = 0; j < word_count; j++) {
    	printf("len : %d\t%s\n", strlen(word_array[j]), word_array[j]);
    }
    */
    return word_array;
}

static size_t get_word_count(const char* str, const char* delim)
{
    const char* delim_ptr = delim;
    const char* str_ptr = str;
    size_t word_count = 0u;
    size_t spelling_count = 0u;
    /*const char* word_last_ptr = NULL;*/
    
    while (*str_ptr != '\0') {
        delim_ptr = delim;
        while (*delim_ptr != '\0') {
            if (*str_ptr == *delim_ptr) {
                if (spelling_count == 0) {
                    goto next_ptr;
                } else {
                    /*word_last_ptr = str_ptr - 1;
                    printf("word_first_ptr : %c\t word_last_ptr : %c\t spell_count : %d\n", *(str_ptr - spelling_count), *word_last_ptr, spelling_count);*/
                    spelling_count = 0;
                    word_count++;
                    goto next_ptr;
                } 
            } 
            delim_ptr++;
        }
        if (*delim_ptr == '\0' && *(str_ptr + 1) == '\0') {
            /*word_last_ptr = str_ptr;*/
            spelling_count++;
            /*printf("word_first_ptr : %c\t word_last_ptr : %c\t spell_count : %d\n", *(str_ptr - spelling_count + 1), *word_last_ptr, spelling_count);*/
            word_count++;
            goto next_ptr;
        }
        spelling_count++;
next_ptr:
        str_ptr++;
    }

    return word_count;
}

static void get_array(const char* str, const char* delim, char** words)
{
    char** word_array = NULL;
    const char* delim_ptr = delim;
    const char* str_ptr = str;
    size_t spelling_count = 0u;
    size_t word_count = 0u;
    size_t i = 0u;
    
    word_array = words;
    
    while (*str_ptr != '\0') {
        delim_ptr = delim;
        while (*delim_ptr != '\0') {
            if (*str_ptr == *delim_ptr) {
                if (spelling_count == 0) {
                    goto next_ptr;
                } else {
                    word_array[i] = (char*)malloc(spelling_count * sizeof(char) + 1);
                    strncpy(word_array[i], str_ptr - spelling_count, spelling_count);
                    word_array[i++][spelling_count] = '\0';
                    spelling_count = 0;
                    word_count++;
                    goto next_ptr;
                }
            }
            delim_ptr++;
        }
        if (*delim_ptr == '\0' && *(str_ptr + 1) == '\0') {
            spelling_count++;
            word_array[i] = (char*)malloc(spelling_count * sizeof(char) + 1);
            strncpy(word_array[i], str_ptr - spelling_count + 1, spelling_count);
            word_array[i++][spelling_count] = '\0';
            word_count++;
            goto next_ptr;
        }
        spelling_count++;
next_ptr:
        str_ptr++;
    }

    word_array[i] = NULL;
}
