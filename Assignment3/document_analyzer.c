/*#define _CRT_SECURE_NO_WARNINGS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

enum { MAX_LENGTH = 1024 };

static size_t s_total_word_count = 0u;
static size_t s_total_sentence_count = 0u;
static size_t s_total_paragraph_count = 0u;

static char**** s_pDocu = NULL;

static FILE* s_doc;

static void get_paragraph_count();

int load_document(const char* document)
{
    const char* ptr = NULL;
    char str[MAX_LENGTH] = "";
    unsigned char check_just_new_line = 0;
    size_t word_count = 0u;
    size_t sentence_count = 0;
    size_t i = 0u;
    size_t j = 0u;
    size_t n = 0u;
    const char* tmp_ptr = NULL;
    const char* tmp_word_ptr = NULL;
    size_t spell_count = 0u;

    s_doc = fopen(document, "r");
    if (s_doc == NULL) {
        perror("error while opening document");
        return FALSE;
    }

    get_paragraph_count();
    s_pDocu = (char****)malloc(sizeof(char***) * s_total_paragraph_count);

    while (fgets(str, MAX_LENGTH, s_doc) != NULL) {
        ptr = str;
        check_just_new_line = TRUE;
        while (*ptr != '\0') {
            if (*ptr == '.' || *ptr == '!' || *ptr == '?') {
                sentence_count++;
                if (*(ptr + 1) == ' ') {
                    ptr++;
                }
            }

            if (*ptr != '\n') {
                check_just_new_line = FALSE;
            }

            ptr++;
        }

        if (check_just_new_line == FALSE && *ptr == '\0') {
            s_pDocu[i] = (char***)malloc(sizeof(char**) * (sentence_count + 1));
            s_pDocu[i][sentence_count] = NULL;

            tmp_ptr = str;
            tmp_word_ptr = str;
            while (*tmp_ptr != '\0') {
                if (*tmp_ptr == ' ' || *tmp_ptr == ',') {
                    word_count++;
                    tmp_ptr++;
                }
                if (*tmp_ptr == '.' || *tmp_ptr == '!' || *tmp_ptr == '?') {
                    word_count++;
                    s_total_word_count += word_count;
                    s_pDocu[i][j] = (char**)malloc(sizeof(char*) * (word_count + 1));
                    s_pDocu[i][j][word_count] = NULL;

                    /**/
                    while (tmp_word_ptr != (tmp_ptr + 1)) {
                        if (*tmp_word_ptr == ' ' || *tmp_word_ptr == ',' || *tmp_word_ptr == '.' || *tmp_word_ptr == '!' || *tmp_word_ptr == '?') {
                            if (spell_count != 0) {
                                s_pDocu[i][j][n] = (char*)malloc(sizeof(char) * (spell_count + 1));
                                strncpy(s_pDocu[i][j][n], tmp_word_ptr - spell_count, spell_count);
                                s_pDocu[i][j][n++][spell_count] = '\0';
                                spell_count = 0;
                                goto next_ptr;
                            }
                            else {
                                goto next_ptr;
                            }

                        }

                        spell_count++;
                    next_ptr:
                        tmp_word_ptr++;
                    }
                    /**/
                    n = 0;
                    if (*(tmp_ptr + 1) == ' ') {
                        tmp_ptr++;
                    }

                    word_count = 0;
                    j++;
                }
                tmp_ptr++;
            }
            i++;
            j = 0;
            puts("");
        }

        s_total_sentence_count += sentence_count;
        sentence_count = 0;
    }

    if (fclose(s_doc) == EOF) {
        perror("error while closing document");
    }

    return TRUE;
}

void dispose(void)
{
    char**** p_para = s_pDocu;
    char*** p_sen = NULL;
    char** p_word = NULL;
    size_t i = 0u;

    for (i = 0; i < s_total_paragraph_count; i++) {
        p_sen = p_para[i];
        while (*p_sen != NULL) {
            p_word = *p_sen;
            while (*p_word != NULL) {
                free(*p_word);
                *p_word = NULL;
                p_word++;
            }
            free(*p_sen);
            *p_sen = NULL;
            p_sen++;
        }

        free(p_para[i]);
        p_para[i] = NULL;
    }
    free(p_para);
    p_para = NULL;
    printf("finish dispose s_pDocu\n");
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
    if (s_doc == NULL || paragraph_index >= s_total_paragraph_count) {
        return NULL;
    }

    return (const char***)s_pDocu[paragraph_index];
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    const char*** p = paragraph;
    const char** pp = NULL;
    size_t count = 0u;

    while (*p != NULL) {
        pp = *p;
        while (*pp++ != NULL) {
            count++;
        }
        p++;
    }

    return count;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    const char*** p = paragraph;
    size_t count = 0u;
    while (*p++ != NULL) {
        count++;
    }

    return count;
}

const char** get_sentence_or_null(const size_t paragraph_index, const size_t sentence_index)
{
    const char*** p = (const char***)s_pDocu[paragraph_index];
    size_t i = 0u;

    if (s_doc == NULL || paragraph_index >= s_total_paragraph_count) {
        return NULL;
    }

    while (i <= sentence_index) {
        if (*(p + i) == NULL) {
            return NULL;
        }
        i++;
    }

    return p[sentence_index];
}

size_t get_sentence_word_count(const char** sentence)
{
    const char** p = sentence;
    size_t count = 0u;

    while (*p++ != NULL) {
        count++;
    }

    return count;
}

int print_as_tree(const char* filename)
{
    size_t i = 0u;
    size_t n = 0u;
    const char**** p_para = (const char****)s_pDocu;
    const char*** p_sen = NULL;
    const char** p_word = NULL;

    s_doc = fopen(filename, "w");
    if (s_doc == NULL) {
        perror("error while opening document");
        return FALSE;
    }

    for (i = 0; i < s_total_paragraph_count; i++) {
        fprintf(s_doc, "Paragraph %d:\n", i);
        p_sen = p_para[i];
        while (*p_sen != NULL) {
            p_word = *p_sen;
            fprintf(s_doc, "    Sentence %d:\n" ,n++);
            while (*p_word != NULL) {
                fprintf(s_doc, "        %s\n", *p_word);
                p_word++;
            }
            p_sen++;
        }
        n = 0;
    }

    fclose(s_doc);

    return TRUE;
}

static void get_paragraph_count()
{
    const char* ptr = NULL;
    char str[MAX_LENGTH] = "";
    unsigned char check_just_new_line = 0;

    while (fgets(str, MAX_LENGTH, s_doc) != NULL) {
        ptr = str;
        check_just_new_line = TRUE;
        while (*ptr != '\0') {
            if (*ptr != '\n') {
                check_just_new_line = FALSE;
            }
            ptr++;
        }

        if (check_just_new_line == FALSE && *ptr == '\0') {
            s_total_paragraph_count++;
        }
    }
    rewind(s_doc);
}
