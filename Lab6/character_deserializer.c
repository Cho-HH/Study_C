/*#define _CRT_SECURE_NO_WARNINGS*/
#include <stdio.h>
#include <string.h>
#include "character_deserializer.h"

void read_ver_1(character_v3_t* out_character, FILE* file);
void read_ver_2(character_v3_t* out_character, FILE* file);
void read_ver_3(character_v3_t* out_character, FILE* file);

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* file;
    const char* check_version = NULL;
    
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("error while opening file");
        return -1;
    }

    check_version = filename + strlen(filename) - 5;

    switch (*check_version) {
    case '1':
        read_ver_1(out_character, file);
        fclose(file);
        return 1;
        break;
    case '2':
        read_ver_2(out_character, file);
        fclose(file);
        return 2;
        break;
    case '3':
        read_ver_3(out_character, file);
        fclose(file);
        return 3;
        break;
    default:
        fclose(file);
        return -1;
        break;
    }
    
    return -1;
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
            sprintf(out_character->name, "%s%d", name, value[i]);	
            out_character->name[MAX_NAME - 1] = '\0';			
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
}

void read_ver_2(character_v3_t* out_character, FILE* file)
{
    char buffer[MAX_BUFFER] = { 0, };
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

    sscanf(buffer, "%s %d %d %d %d %d %d %d %d %d", out_character->name, &out_character->level, &out_character->strength, &out_character->dexterity, &out_character->intelligence, &out_character->armour, &out_character->evasion, &magic_resist, &out_character->health, &out_character->mana);
    out_character->name[MAX_NAME - 1] = '\0';
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    out_character->elemental_resistance.fire = magic_resist / 3;
    out_character->elemental_resistance.cold = magic_resist / 3;
    out_character->elemental_resistance.lightning = magic_resist / 3;
}

void read_ver_3(character_v3_t* out_character, FILE* file)
{
    char buffer[MAX_BUFFER] = { 0, };
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
    
    sscanf(buffer, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d", out_character->name, &out_character->level, &out_character->health, &out_character->mana, &out_character->strength, &out_character->dexterity, &out_character->intelligence, &out_character->armour, &out_character->evasion, &out_character->elemental_resistance.fire, &out_character->elemental_resistance.cold, &out_character->elemental_resistance.lightning, &out_character->leadership, &out_character->minion_count);
    out_character->name[MAX_NAME - 1] = '\0';
	
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
            sscanf(buffer, "%s %d %d %d", out_character->minions[i].name, &out_character->minions[i].health, &out_character->minions[i].strength, &out_character->minions[i].defence);
            out_character->minions[i].name[MAX_NAME - 1] = '\0';
        }
    }
}
