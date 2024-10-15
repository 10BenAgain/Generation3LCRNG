#ifndef POKEMON_H
#define POKEMON_H

#include <stdint.h>

extern const char* gender_s[];
extern const char* shiny_types[];
extern const char* encounter_category[];




typedef struct {
    int key;
    const char *name;
} Nature;

typedef struct {
    int key;
    float mults[5];
} NatureMult;

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

uint8_t get_gender(uint32_t PID, GenderRatio gr);

typedef struct {
    uint32_t dex;
    const char* name;
    uint8_t base_IVs[6];
    GenderRatio gr;
    const char *ab0;
    const char *ab1;
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
extern const NatureMult nature_mults[25];


const char* get_nature_str(uint8_t key);
const char* get_gender_str(uint8_t key);
uint8_t is_shiny(uint32_t PID, uint32_t TID, uint32_t SID);
uint8_t get_hp_value(uint8_t *IVs);
uint8_t get_hp_power(uint8_t *IVs);
uint8_t get_unown_shape(uint32_t PID);
char unown_symbols(int val);
uint8_t* get_iv_range(int level, Nature nature, int base_stat, int stat_total, int stat_num, int ev);


#endif
