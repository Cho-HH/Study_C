//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t todo;
    todo.task_count = 0;
    todo.max_list_size = max_size;
    todo.todo_hashmap = (todo_t*)malloc(sizeof(todo_t) * max_size);
    for (size_t i = 0; i < max_size; i++) {
        todo.todo_hashmap[i].priority = INT32_MIN;
        todo.todo_hashmap[i].task = NULL;
    }
    
    return todo;
}

void finalize_todo_list(todo_list_t* todo_list)
{	    
    for (size_t i = 0; i < todo_list->max_list_size; i++) {
        if (todo_list->todo_hashmap[i].task != NULL) {
            free(todo_list->todo_hashmap[i].task);
        }
    }
    
    free(todo_list->todo_hashmap);
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->max_list_size <= todo_list->task_count) {
        return false;
    }
    
    size_t str_len = strlen(task);
    for (size_t i = 0; i < todo_list->max_list_size; i++) {
        if (todo_list->todo_hashmap[i].task == NULL) {
            todo_list->todo_hashmap[i].priority = priority;
            todo_list->todo_hashmap[i].task = (char*)malloc(sizeof(char) * (str_len + 1));
            strcpy(todo_list->todo_hashmap[i].task, task);
            todo_list->todo_hashmap[i].task[str_len] = '\0';
            break;
        }
    }
    
    todo_list->task_count++;
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list->task_count == 0) {
        return false;
    }
    
    int32_t check_priority = INT32_MIN;
    size_t index = 0;
    
    for (size_t i = 0; i < todo_list->max_list_size; i++) {
        if (check_priority < todo_list->todo_hashmap[i].priority) {
            check_priority = todo_list->todo_hashmap[i].priority;
            index = i;
        }
    }
    
    free(todo_list->todo_hashmap[index].task);
    todo_list->todo_hashmap[index].task = NULL;
    todo_list->todo_hashmap[index].priority = INT32_MIN;
    
    todo_list->task_count--;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->task_count == 0) {
        return NULL;
    }
    
    int32_t check_priority = INT32_MIN;
    size_t index = 0;
    for (size_t i = 0; i < todo_list->max_list_size; i++) {
        if (check_priority < todo_list->todo_hashmap[i].priority) {
            check_priority = todo_list->todo_hashmap[i].priority;
            index = i;
        }
    }
    
    /*printf("index : %d\n", index);
    printf("task : %s\n", todo_list->todo_hashmap[index].task);*/
    return todo_list->todo_hashmap[index].task;
}

size_t get_count(const todo_list_t* todo_list)
{
    /*size_t task_list_count = _msize(todo_list->todo_hashmap) / sizeof(todo_t);
    for (size_t i = 0; i < task_list_count; i++) {
        if (todo_list->todo_hashmap[i].task != NULL) {
            printf("priority : %d\ttask : %s\n", todo_list->todo_hashmap[i].priority, todo_list->todo_hashmap[i].task);
        }
    }
    printf("task_count : %d\n", todo_list->task_count);*/
    return todo_list->task_count;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->task_count == 0 ? true : false;
}
