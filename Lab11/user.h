#ifndef USER_H
#define USER_H

typedef struct {
    size_t id;
    char username[51];
    char padding1;
    char email[51];
    char padding2;
    char password[51];
    char padding3;
} user_t;

#endif /*USER_H*/
