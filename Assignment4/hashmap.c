/*#define _CRT_SECURE_NO_WARNINGS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t(*p_hash_func)(const char* key))
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
    size_t hash_key = hashmap->hash_func(key) % hashmap->length;
    node_t* newNode = NULL;
    node_t* dummyNode = NULL;
    node_t* current_Node = hashmap->plist[hash_key];
    size_t check_dummy_node = 0;
    
    while (current_Node != NULL) {
        if (check_dummy_node == 0) {
            current_Node = current_Node->next;
            if (current_Node == NULL) {
                break;
            }
            check_dummy_node = 1;
        }
        if (strcmp(current_Node->key, key) == 0) {
            return FALSE;
        }		
        current_Node = current_Node->next;
    }
    
    /*더미노드 == 헤드*/
    if (hashmap->plist[hash_key] == NULL) {
        dummyNode = (node_t*)malloc(sizeof(node_t));
        dummyNode->key = NULL;
        dummyNode->value = 0;
        dummyNode->next = NULL;
        hashmap->plist[hash_key] = dummyNode;
        /*puts("create Dummey Node!");*/
    }
    
    newNode = (node_t*)malloc(sizeof(node_t));
    str_len = strlen(key);
    newNode->key = (char*)malloc(sizeof(char) * (str_len + 1));
    strcpy(newNode->key, key);
    newNode->key[str_len] = '\0';
    newNode->value = value;
    
    newNode->next = hashmap->plist[hash_key]->next;
    hashmap->plist[hash_key]->next = newNode;
    /*puts("create Node");*/
    
    
    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t hash_key = hashmap->hash_func(key) % hashmap->length;
    node_t* currentNode = hashmap->plist[hash_key];	
    size_t check_dummy_node = 0;
    
    while (currentNode != NULL) {
        if (check_dummy_node == 0) {
            currentNode = currentNode->next;
            if (currentNode == NULL) {
                break;
            }
            check_dummy_node = 1;
        }
        if (strcmp(currentNode->key, key) == 0) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }
    
    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    size_t hash_key = hashmap->hash_func(key) % hashmap->length;
    node_t* currentNode = hashmap->plist[hash_key];
    size_t check_dummy_node = 0;
    
    while (currentNode != NULL) {
        if (check_dummy_node == 0) {
            currentNode = currentNode->next;
            if (currentNode == NULL) {
                break;
            }
            check_dummy_node = 1;
        }
        if (strcmp(currentNode->key, key) == 0) {
            currentNode->value = value;
            return TRUE;
        }
        currentNode = currentNode->next;
    }
    
    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t hash_key = hashmap->hash_func(key) % hashmap->length;
    node_t* prev_Node = hashmap->plist[hash_key];
    node_t* current_Node = NULL;
    
    if (prev_Node == NULL) {
        return FALSE;
    }
    
    current_Node = prev_Node->next;
    while (current_Node != NULL) {
        if (strcmp(current_Node->key, key) == 0) {
            prev_Node->next = current_Node->next;
            free(current_Node);
            if (prev_Node->next == NULL && prev_Node == hashmap->plist[hash_key]) {
                free(prev_Node);
                hashmap->plist[hash_key] = NULL;
            }
            return TRUE;
        }
        prev_Node = current_Node;
        current_Node = current_Node->next;
    }
    
    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i = 0;
    node_t* currentNode = NULL;
    node_t* nextNode = NULL;
    
    for (i = 0; i < hashmap->length; i++) {
        if (hashmap->plist[i] != NULL) {
            currentNode = hashmap->plist[i];
            while (currentNode != NULL) {
                nextNode = currentNode->next;
                free(currentNode);
                currentNode = nextNode;
            }
        }
    }
    
    free(hashmap->plist);
    puts("free_list");
    free(hashmap);
    puts("free_haspmap");
}
