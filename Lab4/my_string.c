#include <stdio.h>
#include "my_string.h"

static char* s_token_ptr = NULL;
	
static size_t get_string_length(const char* const str)
{
    size_t str_length = 0u;
    const char* str_ptr = (const char*)str;
	
    while (*str_ptr != '\0') {
        ++str_ptr;
        ++str_length;
    }
	
    return str_length;
}

void reverse(char* str)
{
    size_t str_length = get_string_length(str);
    char temp = 0;
    char* str_ptr = str + str_length - 1;
    char* first_ptr = str;

    while (first_ptr < str_ptr) {
        temp = *str_ptr;
        *str_ptr = *first_ptr;
        *first_ptr = temp;
        ++first_ptr;
        --str_ptr;
    }		
    
    printf("%s\n", str);
}

int index_of(const char* str, const char* word)
{
    const char* str_ptr = str;
    const char* check_str_ptr = str_ptr;
    const char* word_ptr = word;
    const char* save_str_ptr = str_ptr;
	
    if (*word == '\0') {
        return 0;
    }
	
    while (*str_ptr != '\0') {
        if (*str_ptr == *word_ptr) {
            check_str_ptr = str_ptr;
            save_str_ptr = str_ptr;
            while (*check_str_ptr == *word_ptr) {
                ++word_ptr;
                ++check_str_ptr;
                if (*word_ptr == '\0') {
                    printf("index : %d\n",save_str_ptr - str);
                    return save_str_ptr - str;
                }
            }
        }
        word_ptr = word;
        ++str_ptr;
    }
	
    printf("index : -1\n");
    return -1;	
}

void reverse_by_words(char* str)
{
    char temp = 0;
    char* word_first_ptr = NULL;
    char* word_last_ptr = NULL;
    const char* check_ptr = (const char*)str;
    
    while (*check_ptr != '\0') {
        word_first_ptr = (char*)check_ptr;
        while (*check_ptr != ' ' && *check_ptr != '\0') {
            word_last_ptr = (char*)check_ptr;
            ++check_ptr;
        }
	
        while (word_first_ptr < word_last_ptr) {
            temp = *word_first_ptr;
            *word_first_ptr = *word_last_ptr;
            *word_last_ptr = temp;
            ++word_first_ptr;
            --word_last_ptr;
        }
        if (*check_ptr == ' ') {
            ++check_ptr;
        }
    }
    	
    printf("%s\n", str);
}

char* tokenize(char* str_or_null, const char* delims)
{
    const char* save_token_ptr = NULL;
    const char* delims_ptr = delims;
    
    if (s_token_ptr == NULL) {
        s_token_ptr = str_or_null;
        if (s_token_ptr == NULL) {
            return NULL;
        }
    }
    if (s_token_ptr != NULL && str_or_null != NULL) {
		s_token_ptr = str_or_null;
	}
	
    save_token_ptr = s_token_ptr;
	/*X  my name is mui*/
    while (*s_token_ptr != '\0') {		        
		delims_ptr = delims;
        while (*delims_ptr != '\0') {
            if (*s_token_ptr == *delims_ptr) {	
			    *s_token_ptr = '\0';	
				++s_token_ptr;
				return (char*) save_token_ptr;
            }
            ++delims_ptr;
        }
        ++s_token_ptr;
    }
    
    return NULL;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{	
    char* token_first_ptr = tokenize(str_or_null, delims);
    const char* const save_token_first_ptr = (const char* const)token_first_ptr;
    size_t token_length = get_string_length(token_first_ptr);
    char temp = 0;
    char* token_last_ptr = token_first_ptr + token_length - 1;
    
    while (token_first_ptr < token_last_ptr) {
        temp = *token_first_ptr;
        *token_first_ptr = *token_last_ptr;
        *token_last_ptr = temp;
        ++token_first_ptr;
        --token_last_ptr;
    }
    
    printf("reverse token : %s\n",save_token_first_ptr);
    return (char*)save_token_first_ptr;
}
