#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

enum { MAX_LENGTH = 512 };

static size_t s_total_word_count = 0u;
static size_t s_total_sentence_count = 0u;
static size_t s_total_paragraph_count = 0u;

static char**** s_pdocu = NULL;

static FILE* s_doc = NULL;

int load_document(const char* document)
{
    char buffer[MAX_LENGTH] = { 0, };
    unsigned char just_new_line = 0;

    size_t i = 0u;
    size_t j = 0u;
    char**** tmp_docu_ptr = NULL;
    char** tmp_sen_ptr = NULL;

    size_t sentence_count = 0u;
    size_t word_count = 0u;

    char tmp_sentence[MAX_LENGTH] = { 0, };
    char* sentence_token = NULL;
    size_t str_len = 0u;
    char** token_copy = NULL;


    if (s_doc != NULL) {
        perror("already exist opening file\n");
        return FALSE;
    }

    s_doc = fopen(document, "r");
    if (s_doc == NULL) {
        perror("error while opening document");
        return FALSE;
    }

    s_pdocu = (char****)malloc(sizeof(char***));
    while (fgets(buffer, MAX_LENGTH, s_doc) != NULL) {
        just_new_line = FALSE;
        if (buffer[0] == '\n') {
            just_new_line = TRUE;
        }

        if (just_new_line == FALSE) {
            s_total_paragraph_count++;
            tmp_docu_ptr = (char****)realloc(s_pdocu, sizeof(char***) * s_total_paragraph_count);
            if (tmp_docu_ptr != NULL) {
                s_pdocu = tmp_docu_ptr;
            }

            /*token화한 문장을 임시 문자열에 저장*/
            strncpy(tmp_sentence, buffer, MAX_LENGTH);
            tmp_sentence[MAX_LENGTH - 1] = '\0';
            sentence_token = strtok(tmp_sentence, ".?!");
            while (sentence_token != NULL) {
                if (strcmp(sentence_token, "\n") == 0) {
                    break;
                }
                else {
                    sentence_count++;
                    tmp_sen_ptr = (char**)realloc(token_copy, sizeof(char*) * sentence_count);
                    if (tmp_sen_ptr != NULL) {
                        token_copy = tmp_sen_ptr;
                    }
                    str_len = strlen(sentence_token);
                    token_copy[i] = (char*)malloc(sizeof(char) * (str_len + 1));
                    strcpy(token_copy[i], sentence_token);
                    token_copy[i++][str_len] = '\0';
                }
                sentence_token = strtok(NULL, ".?!");
            }
            /**/

            s_pdocu[s_total_paragraph_count - 1] = (char***)malloc(sizeof(char**) * (sentence_count + 1));
            s_pdocu[s_total_paragraph_count - 1][sentence_count] = NULL;


            for (i = 0; i < sentence_count; i++) {
                sentence_token = strtok(token_copy[i], " ,");
                s_pdocu[s_total_paragraph_count - 1][i] = (char**)malloc(sizeof(char*));
                while (sentence_token != NULL) {
                    word_count++;
                    tmp_sen_ptr = (char**)realloc(s_pdocu[s_total_paragraph_count - 1][i], sizeof(char*) * (word_count + 1));
                    if (tmp_sen_ptr != NULL) {
                        s_pdocu[s_total_paragraph_count - 1][i] = tmp_sen_ptr;
                    }
                    s_pdocu[s_total_paragraph_count - 1][i][word_count] = NULL;
                    str_len = strlen(sentence_token);
                    s_pdocu[s_total_paragraph_count - 1][i][j] = (char*)malloc(sizeof(char) * (str_len + 1));
                    strcpy(s_pdocu[s_total_paragraph_count - 1][i][j], sentence_token);
                    s_pdocu[s_total_paragraph_count - 1][i][j++][str_len] = '\0';

                    sentence_token = strtok(NULL, " ,");
                }
                j = 0;
                s_total_word_count += word_count;
                word_count = 0;
            }
            s_total_sentence_count += sentence_count;


            for (i = 0; i < sentence_count; i++) {
                printf("free mem\n");
                free(token_copy[i]);
                token_copy[i] = NULL;
            }
            free(token_copy);
            token_copy = NULL;

            i = 0;
        }
        sentence_count = 0;
    }

    if (fclose(s_doc) == EOF) {
        perror("error while closing document");
    }

    return TRUE;
}

void dispose(void)
{
    char**** p_para = s_pdocu;
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
    printf("finish dispose s_pdocu\n");
    s_pdocu = NULL;
    s_doc = NULL;
    s_total_word_count = 0;
    s_total_sentence_count = 0;
    s_total_paragraph_count = 0;
}

size_t get_total_word_count(void)
{
    if (s_doc == NULL) {
        return 0;
    }

    return s_total_word_count;
}

size_t get_total_sentence_count(void)
{
    if (s_doc == NULL) {
        return 0;
    }

    return s_total_sentence_count;
}

size_t get_total_paragraph_count(void)
{
    if (s_doc == NULL) {
        return 0;
    }

    return s_total_paragraph_count;
}

const char*** get_paragraph_or_null(const size_t paragraph_index)
{
    if (s_doc == NULL || paragraph_index >= s_total_paragraph_count) {
        return NULL;
    }

    return (const char***)s_pdocu[paragraph_index];
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
    const char*** p = NULL;
    size_t i = 0u;

    if (s_doc == NULL || paragraph_index >= s_total_paragraph_count) {
        return NULL;
    }

    p = (const char***)s_pdocu[paragraph_index];

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
    const char**** p_para = (const char****)s_pdocu;
    const char*** p_sen = NULL;
    const char** p_word = NULL;

    if (s_total_word_count == 0) {
        return FALSE;
    }

    s_doc = fopen(filename, "w");
    if (s_doc == NULL) {
        perror("error while opening document");
        return FALSE;
    }

    for (i = 0; i < s_total_paragraph_count; i++) {
        if (i > 0) {
            fprintf(s_doc, "\n\n");
        }
        fprintf(s_doc, "Paragraph %d:", i);
        p_sen = p_para[i];
        while (*p_sen != NULL) {
            p_word = *p_sen;
            fprintf(s_doc, "\n    Sentence %d:", n++);
            while (*p_word != NULL) {
                fprintf(s_doc, "\n        %s", *p_word);
                p_word++;
            }
            p_sen++;
        }
        n = 0;
    }

    fclose(s_doc);

    return TRUE;
}
