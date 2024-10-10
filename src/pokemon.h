#ifndef POKEMON_H
#define POKEMON_H

#include <stdint.h>

extern const char* shiny_types[];
extern const char* encounter_category[];

const char* get_nature_str(uint8_t key);
int is_shiny(uint32_t PID, uint32_t TID, uint32_t SID);
int get_hp_value(uint8_t *IVs);
int get_hp_power(uint8_t *IVs);

typedef struct {
    int key;
    const char *name;
} Nature;

typedef enum {
    MaleOnly    = 0,
    FemaleOnly  = 1,
    Unknown     = 3,
    F1M7        = 0x1F,
    F1M3        = 0x40,
    F1M1        = 0x1A,
    F3M1        = 0x40,
} GenderRatio;

typedef struct {
    int key;
    const char *type;
} HiddenPower;

int get_gender(uint32_t PID, GenderRatio gr);

typedef struct {
    uint32_t dex;
    const char* name;
    uint8_t base_IVs[6];
    GenderRatio gr;
} Pokemon;

typedef enum {
        Starters,
        Fossils,
        Gifts,
        GameCorner,
        Stationary,
        Legends,
        Events,
        Roamers
} Category;

typedef struct {
    Category cat;
    const char* mon;
    int level;
} Encounter;

extern const Nature natures[25];
extern const Pokemon pokemon[151];
extern const Encounter StaticEncounters[];
extern const HiddenPower HP[16];

#endif