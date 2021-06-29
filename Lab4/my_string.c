#include <stdio.h>
#include "my_string.h"

static size_t get_string_length(const char* const str)
{
    size_t str_length = 0u;
    const char* str_ptr = (const char*)str;

    if (str == NULL) {
        return -1;
    }

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

    /*printf("reverse : %s\n", str);*/
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
                    printf("index : %d\n", save_str_ptr - str);
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
    static char* s_token_ptr = NULL;
    size_t token_count = 0u;
    const char* delims_ptr = delims;

    if (s_token_ptr == NULL) {
        s_token_ptr = str_or_null;
        if (s_token_ptr == NULL) {
            return NULL;
        }
    }
    if (*s_token_ptr == '\0') {
        return NULL;
    }

    while (*s_token_ptr != '\0') {
        delims_ptr = delims;
        while (*delims_ptr != '\0') {
            if (*s_token_ptr == *delims_ptr) {
                /* 실행되자마자 s_token_ptr가 delims면 다음 포인터로*/
                if (token_count == 0) {
                    goto next_ptr;
                }
                else {
                    *s_token_ptr = '\0';
                    goto end;
                }
            }
            delims_ptr++;
        }
        /*delims가 아닌 글자가 들어오면 ++ */
        token_count++;
next_ptr:
        s_token_ptr++;
    }

/*s_token_ptr == '\0' 일 때*/
end:
    return s_token_ptr++ - token_count;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* token_first_ptr = tokenize(str_or_null, delims);

    if (token_first_ptr == NULL) {
        return NULL;
    }

    reverse(token_first_ptr);

    printf("reverse token : %s\n", token_first_ptr);
    return token_first_ptr;
}
