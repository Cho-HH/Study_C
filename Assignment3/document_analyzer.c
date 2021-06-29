#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

enum { MAX_LENGTH = 1024 };

static size_t s_total_word_count = 0u;
static size_t s_total_sentence_count = 0u;
static size_t s_total_paragraph_count = 0u;

static char*** s_pParagraph = NULL;

static FILE* s_doc;

int load_document(const char* document)
{
    const char* ptr = NULL;
    char str[MAX_LENGTH] = "";
    char* word = NULL;
    unsigned char check_just_new_line = 0;
    const char* delims = " ,";
    const char* sentence_delims = ".!?\n";
    char* sentence = NULL;
    size_t str_len = 0u;
    size_t word_count = 0u;
    size_t sentence_count = 0;
    size_t para_count = 0;
    size_t i = 0u;
    char*** tmp_ptr = NULL;
    char tmp_str[MAX_LENGTH] = "";

    s_doc = fopen(document, "r");
    if (s_doc == NULL) {
        perror("error while opening document");
        return FALSE;
    }

    while (fgets(str, MAX_LENGTH, s_doc) != NULL) {
        printf("%s", str);
        puts("");
        ptr = str;
        check_just_new_line = TRUE;
        while (*ptr != '\0') {
            if (*ptr == ' ' || *ptr == ',') {
                word_count++;
                ptr++;
            }
            else if (*ptr == '.' || *ptr == '!' || *ptr == '?') {
                sentence_count++;
            }

            if (*ptr != '\n') {
                check_just_new_line = FALSE;
            }

            ptr++;
        }

        if (check_just_new_line == FALSE && *ptr == '\0') {
            para_count++;
            word_count++;
        }
       
        /* printf("\nthis_word_count : %d\n", word_count);
         printf("this_sentence_count : %d\n", sentence_count);
         printf("this_para_count : %d\n", para_count);*/
        s_total_word_count += word_count;
        s_total_sentence_count += sentence_count;
        s_total_paragraph_count += para_count;
        

        /*printf("total_word_count : %d\n", s_total_word_count);
        printf("total_sentence_count : %d\n", s_total_sentence_count);
        printf("total_paragraph_count : %d\n", s_total_paragraph_count);*/

        tmp_ptr = (char***)realloc(s_pParagraph, s_total_paragraph_count * sizeof(char**));
        if (tmp_ptr != NULL) {
            s_pParagraph = tmp_ptr;
        }

        sentence = strtok(str, sentence_delims);
        while (sentence != NULL) {
            printf("%s\n", sentence);
            sentence = strtok(NULL, sentence_delims);
          
           /* for (i = 0; i < s_total_sentence_count; i++) {
                *(s_pParagraph + i) = (char**)realloc(s_pParagraph[i] ,sentence_count * sizeof(char*));
                *(s_pParagraph + i)  sentence;
            }*/
            

            
        }

        word_count = 0u;
        sentence_count = 0u;
        para_count = 0u;

    }


    free(s_pParagraph);
    if (fclose(s_doc) == EOF) {
        perror("error while closing document");
    }

    return TRUE;
}

void dispose(void)
{
    free(s_pParagraph);
}

size_t get_total_word_count(void)
{
    return s_total_word_count;
}

size_t get_total_sentence_count(void)
{
    return s_total_sentence_count;
}

size_t get_total_paragraph_count(void)
{
    return s_total_paragraph_count;
}

const char*** get_paragraph_or_null(const size_t paragraph_index)
{
    if (s_doc == NULL || paragraph_index  >= s_total_paragraph_count) {
        return NULL;
    }


}

size_t get_paragraph_word_count(const char*** paragraph)
{

}

size_t get_paragraph_sentence_count(const char*** paragraph)
{

}

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index)
{

}

size_t get_sentence_word_count(const char** sentence)
{

}

int print_as_tree(const char* filename)
{

}
