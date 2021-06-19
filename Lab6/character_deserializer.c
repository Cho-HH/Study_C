/*#define _CRT_SECURE_NO_WARNINGS*/
#include <stdio.h>
#include <string.h>
#include "character_deserializer.h"

void read_ver_1(character_v3_t* out_character, FILE* file);
void read_ver_2(character_v3_t* out_character, FILE* file);
void read_ver_3(character_v3_t* out_character, FILE* file);
void check_name(char character_name[], const char* name);

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* file;
    char buffer[MAX_BUFFER] = { 0, };
    const char* check_version = NULL;
	
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("error while opening file");
        return -1;
    }

    fgets(buffer, MAX_BUFFER, file);
    /*다음줄을 가리키고 있는 스트림위치를 다시 처음으로 되돌린다.*/
    rewind(file);
    check_version = buffer;
    while (*check_version != '\0' && *check_version != '\n') {
        if (*check_version == ':') {
            read_ver_1(out_character, file);
            return 1;
        } else if (*check_version == '|') {
            read_ver_3(out_character, file);
            return 3;
        }
        check_version++;
    }
       
    read_ver_2(out_character, file);
    return 2;
}

void read_ver_1(character_v3_t* out_character, FILE* file)
{
    size_t i = 0;
    char buffer[MAX_BUFFER] = { 0, };
    char* tmp = NULL;
    char key[8][MAX_BUFFER] = { 0, };
    int value[8] = { 0, };
    char name[MAX_NAME] = "player_";
    
    fgets(buffer, MAX_BUFFER, file);
    tmp = buffer;
    while (*tmp != '\0') {
        if (*tmp == ':' || *tmp == ',') {
            *tmp = ' ';			
        }
        tmp++;
    }

    sscanf(buffer, "%s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d", key[0], &value[0], key[1], &value[1], key[2], &value[2], key[3], &value[3], key[4], &value[4], key[5], &value[5], key[6], &value[6], key[7], &value[7]);
    	
    for (i = 0; i < 8; i++) {
        if (strcmp(*(key + i), "lvl") == 0) {
            out_character->level = value[i];
            out_character->leadership = value[i] / 10;
        } else if (strcmp(*(key + i), "id") == 0) {
            sprintf(buffer, "%s%d", name, value[i]);
            check_name(out_character->name, buffer);	
        } else if (strcmp(*(key + i), "str") == 0) {
            out_character->strength = value[i];
        } else if (strcmp(*(key + i), "dex") == 0) {
            out_character->dexterity = value[i];
            out_character->evasion = value[i] / 2;
        } else if (strcmp(*(key + i), "intel") == 0) {
            out_character->intelligence = value[i];
        } else if (strcmp(*(key + i), "def") == 0) {
            out_character->armour = value[i];
            out_character->elemental_resistance.fire = value[i] / 12;
            out_character->elemental_resistance.cold = value[i] / 12;
            out_character->elemental_resistance.lightning = value[i] / 12;
        } else if (strcmp(*(key + i), "hp") == 0) {
            out_character->health = value[i];
        } else if (strcmp(*(key + i), "mp") == 0) {
            out_character->mana = value[i];
        } 
    } 
    out_character->minion_count = 0;	
   
    if (fclose(file) == EOF) {
        perror("error while closing file");
    }
}

void read_ver_2(character_v3_t* out_character, FILE* file)
{
    char buffer[MAX_BUFFER] = { 0, };
    char name_buffer[MAX_BUFFER] = { 0, };
    char* tmp = NULL;
    int magic_resist = 0;
    
    fgets(buffer, MAX_BUFFER, file);
    fgets(buffer, MAX_BUFFER, file);
    tmp = buffer;
    while (*tmp != '\0') {
        if (*tmp == ',') {
            *tmp = ' ';
        }
        tmp++;
    }

    sscanf(buffer, "%s %d %d %d %d %d %d %d %d %d", name_buffer, &out_character->level, &out_character->strength, &out_character->dexterity, &out_character->intelligence, &out_character->armour, &out_character->evasion, &magic_resist, &out_character->health, &out_character->mana);
    check_name(out_character->name, name_buffer);
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    out_character->elemental_resistance.fire = magic_resist / 3;
    out_character->elemental_resistance.cold = magic_resist / 3;
    out_character->elemental_resistance.lightning = magic_resist / 3;
	
    if (fclose(file) == EOF) {
        perror("error while closing file");
    }
}

void read_ver_3(character_v3_t* out_character, FILE* file)
{
    char buffer[MAX_BUFFER] = { 0, };
    char name_buffer[MAX_BUFFER] = { 0, };
    char* tmp = NULL;
    size_t i = 0;
    
    fgets(buffer, MAX_BUFFER, file);
    fgets(buffer, MAX_BUFFER, file);
    
    tmp = buffer;
    while (*tmp != '\0') {
        if (*tmp == '|') {
            *tmp = ' ';
        }
        tmp++;
    }
    
    sscanf(buffer, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d", name_buffer, &out_character->level, &out_character->health, &out_character->mana, &out_character->strength, &out_character->dexterity, &out_character->intelligence, &out_character->armour, &out_character->evasion, &out_character->elemental_resistance.fire, &out_character->elemental_resistance.cold, &out_character->elemental_resistance.lightning, &out_character->leadership, &out_character->minion_count);
    check_name(out_character->name, name_buffer);
	
    if (out_character->minion_count > 0) {
        fgets(buffer, MAX_BUFFER, file);
        for (i = 0; i < out_character->minion_count; i++) {
            fgets(buffer, MAX_BUFFER, file);
            tmp = buffer;
            while (*tmp != '\0') {
                if (*tmp == '|') {
                    *tmp = ' ';
                }
                tmp++;
            }
            sscanf(buffer, "%s %d %d %d", name_buffer, &out_character->minions[i].health, &out_character->minions[i].strength, &out_character->minions[i].defence);
            check_name(out_character->minions[i].name, name_buffer);
        }
    }

    if (fclose(file) == EOF) {
        perror("error while closing file");
    }
}

void check_name(char character_name[], const char* name)
{  
    const char* tmp = name;

    while (*tmp != '\0') {
        if ((*tmp < '0' || *tmp > '9') && (*tmp < 'A' || *tmp > 'Z') && *tmp != '_' && (*tmp < 'a' || *tmp > 'z')) {
            return;
        }
        tmp++;
    }
    
    sprintf(character_name, "%s", name);
    character_name[MAX_NAME - 1] = '\0';
}
