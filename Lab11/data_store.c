//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    if (users_or_null == NULL) {
        return NULL;
    }
    
    user_t** check_users = users_or_null;
    
    while (*check_users != NULL) {
        if ((*check_users)->id == id) {
            return *check_users;
        }
        check_users++;
    }
    
    return NULL;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    if (users_or_null == NULL) {
        return NULL;
    }
    
    user_t** check_users = users_or_null;
    
    while (*check_users != NULL) {
        if (strcmp((*check_users)->username, username) == 0) {
            return *check_users;
        }
        check_users++;
    }
    return NULL;
}

bool update_email(user_t** users_or_null, size_t id, const char* email)
{
    if (users_or_null == NULL) {
        return false;
    }
    
    user_t** check_users = users_or_null;
    
    while (*check_users != NULL) {
        if ((*check_users)->id == id) {
            FILE* log = fopen("log.txt", "a");
            if (log == NULL) {
                perror("Failed to open log.txt");
                return false;
            }
            
            char tmp[51] = { 0, };
            strcpy(tmp, (*check_users)->email);
            strcpy((*check_users)->email, email);
            fprintf(log, "TRACE: User %d updated email from ", (*check_users)->id);
#if !defined RELEASE //디버그모드
            fprintf(log, "\"%s\" to \"%s\"\n", tmp, (*check_users)->email);
#elif defined RELEASE //릴리즈모드
            char tmp_email[51] = { 0, };
            char tmp_user_email[51] = { 0, };
            strcpy(tmp_email, email);
            strcpy(tmp_user_email, tmp);
            
            char* check_email_length = tmp_email;
            size_t email_length = 0u;
            while (*check_email_length++ != '@') {
                email_length++;
            }			
            
            if (email_length == 1) {
                tmp_email[0] = '*';
            } else if (email_length == 2) {
                tmp_email[1] = '*';
            } else if (email_length >= 3) {
                check_email_length = tmp_email + 1;
                for (size_t i = 0u; i < email_length - 2; i++) {
                    *check_email_length = '*';
                    check_email_length++;
                }
            }
            
            check_email_length = tmp_user_email;
            email_length = 0u;
            while (*check_email_length++ != '@') {
                email_length++;
            }
            
            if (email_length == 1) {
                tmp_user_email[0] = '*';
            } else if (email_length == 2) {
                tmp_user_email[1] = '*';
            } else if (email_length >= 3) {
                check_email_length = tmp_user_email + 1;
                for (size_t i = 0u; i < email_length - 2; i++) {
                    *check_email_length = '*';
                    check_email_length++;
                }
            }

            
            fprintf(log, "\"%s\" to \"%s\"\n", tmp_user_email, tmp_email);
#endif            
            fclose(log);
            return true;
        }
        check_users++;
    }
    
    return false;
}

bool update_password(user_t** users_or_null, size_t id, const char* password)
{
    if (users_or_null == NULL) {
        return false;
    }
    
    user_t** check_users = users_or_null;
    
    while (*check_users != NULL) {
        if ((*check_users)->id == id) {
            FILE* log = fopen("log.txt", "a");
            if (log == NULL) {
                perror("Failed to open log.txt");
                return false;
            }
            
            char tmp[51] = { 0, };
            strcpy(tmp, (*check_users)->password);
            strcpy((*check_users)->password, password);
            fprintf(log, "TRACE: User %d updated password from ", (*check_users)->id);
#if !defined RELEASE
            fprintf(log, "\"%s\" to \"%s\"\n", tmp, (*check_users)->password);
#elif defined RELEASE
            char tmp_password[51] = { 0, };
            char tmp_user_password[51] = { 0, };
            strcpy(tmp_password, password);
            strcpy(tmp_user_password, tmp);
            char* check_password_length = tmp_password;
            size_t password_length = 0u;
            while (*check_password_length++ != '\0') {
                password_length++;
            }
            
            if (password_length == 1) {
                tmp_password[0] = '*';
            } else if (password_length == 2) {
                tmp_password[1] = '*';
            } else if (password_length >= 3) {
                check_password_length = tmp_password + 1;
                for (size_t i = 0u; i < password_length - 2; i++) {
                    *check_password_length = '*';
                    check_password_length++;
                }
            }
            check_password_length = tmp_user_password;
            password_length = 0u;
            while (*check_password_length++ != '\0') {
                password_length++;
            }
            
            if (password_length == 1) {
                tmp_user_password[0] = '*';
            } else if (password_length == 2) {
                tmp_user_password[1] = '*';
            } else if (password_length >= 3) {
                check_password_length = tmp_user_password + 1;
                for (size_t i = 0u; i < password_length - 2; i++) {
                    *check_password_length = '*';
                    check_password_length++;
                }
            }
            
            fprintf(log, "\"%s\" to \"%s\"\n", tmp_user_password, tmp_password);
#endif
            fclose(log);
            return true;
        }
        check_users++;
    }
    
    return false;
}
