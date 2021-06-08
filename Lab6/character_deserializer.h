#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

enum { 
    MAX_BUFFER = 512,
    /*널문자 제외 50글자*/
    MAX_NAME = 50,
    MAX_MINION = 3
};

typedef struct {
    unsigned int health;
    unsigned int strength;
    unsigned int defence;
    char name[MAX_NAME];
    char padding[2];
} minion_t;

typedef struct {
    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;
} elemental_resistance_t;

typedef struct {
    char name[MAX_NAME];
    char padding[2];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    size_t minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[MAX_MINION];
} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);

#endif /* CHARACTER_DESERIALIZER_H */
