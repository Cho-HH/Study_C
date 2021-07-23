#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int32_t priority;
    char* task;
} todo_t;

typedef struct todo_list {
    size_t task_count;
    size_t max_list_size;
    todo_t* todo_hashmap;
} todo_list_t;

todo_list_t init_todo_list(size_t max_size);

void finalize_todo_list(todo_list_t* todo_list);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(const todo_list_t* todo_list);

size_t get_count(const todo_list_t* todo_list);

bool is_empty(const todo_list_t* todo_list);

#endif /* TODO_LIST_H */
