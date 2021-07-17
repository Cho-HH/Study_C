/*#define _CRT_SECURE_NO_WARNINGS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i = 0u;
    hashmap_t* tmp_hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));
    tmp_hashmap->hash_func = p_hash_func;
    tmp_hashmap->length = length;
    tmp_hashmap->plist = (node_t**)malloc(sizeof(node_t*) * length);
    for (i = 0; i < length; i++) {
        tmp_hashmap->plist[i] = NULL;
    }
    
    return tmp_hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    size_t str_len = 0;
    size_t hash_key = NULL;
    node_t* new_node = NULL;
    node_t* current_node = NULL;

    if (hashmap->hash_func == NULL || hashmap->length == 0 || hashmap->plist == NULL) {
        return FALSE;
    }

    hash_key = hashmap->hash_func(key) % hashmap->length;
    current_node = &(hashmap->plist[hash_key]);

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            return FALSE;
        }		
        current_node = current_node->next;
    }
    
    new_node = (node_t*)malloc(sizeof(node_t));
    str_len = strlen(key);
    new_node->key = (char*)malloc(sizeof(char) * (str_len + 1));
    strcpy(new_node->key, key);
    new_node->key[str_len] = '\0';
    new_node->value = value;
    
    new_node->next = hashmap->plist[hash_key];
    hashmap->plist[hash_key] = new_node;
    /*puts("create Node");*/    
    
    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t hash_key = NULL;
    node_t* current_node = NULL;;

    if (hashmap->hash_func == NULL || hashmap->length == 0 || hashmap->plist == NULL) {
        return FALSE;
    }

    hash_key = hashmap->hash_func(key) % hashmap->length;
    current_node = &(hashmap->plist[hash_key]);

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            return current_node->value;
        }
        current_node = current_node->next;
    }
    
    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    size_t hash_key = NULL;
    node_t* current_node = NULL;;
    
    if (hashmap->hash_func == NULL || hashmap->length == 0 || hashmap->plist == NULL) {
        return FALSE;
    }

    hash_key = hashmap->hash_func(key) % hashmap->length;
    current_node = &(hashmap->plist[hash_key]);

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            current_node->value = value;
            return TRUE;
        }
        current_node = current_node->next;
    }
    
    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t hash_key = NULL;
    node_t** current_node = NULL;;
    node_t* remove_node = NULL;

    if (hashmap->hash_func == NULL || hashmap->length == 0 || hashmap->plist == NULL) {
        return FALSE;
    }

    hash_key = hashmap->hash_func(key) % hashmap->length;
    current_node = &(hashmap->plist[hash_key]);

    while (*current_node != NULL) {
        if (strcmp((*current_node)->key, key) == 0) {
            remove_node = *current_node;
            *current_node = remove_node->next;
            free(remove_node);
            return TRUE;
        }      
        current_node = &((*current_node)->next);
    }
    
    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i = 0;
    node_t* current_node = NULL;
    node_t* next_node = NULL;
    
    for (i = 0; i < hashmap->length; i++) {
        if (hashmap->plist[i] != NULL) {
            current_node = hashmap->plist[i];
            while (current_node != NULL) {
                next_node = current_node->next;
                free(current_node);
                current_node = next_node;
            }
        }
    }
    
    free(hashmap->plist);
    puts("free_list");
    free(hashmap);
    puts("free_haspmap");
}
