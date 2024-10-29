#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdint.h>
#include "rng.h"
#include "pokemon.h"
#include "encounter_table.h"

typedef struct {
    uint32_t TID;
    uint32_t SID;
} Player;

typedef struct {
    uint8_t mon;
    uint32_t PID;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];
    const char* gender;
    const char* hp;
    uint8_t hp_pow;
    uint8_t shiny;
    uint32_t advances;
} StaticEncounter;

typedef struct {
    uint32_t PID;
    uint8_t mon;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];
    uint8_t slot;
    uint8_t level;
    const char* hp;
    uint8_t hp_pow;
    uint8_t shiny;
    uint32_t seed;
    uint32_t advances;
} WildEncounter;

StaticEncounter **generate_M1_encounter_array(Player pl, uint16_t mon, uint16_t seed, uint32_t init, uint32_t max);
WildEncounter **generate_H1_encounter_array(Player pl, AreaEntry aEntry, GameVersion gv, uint16_t seed, uint32_t init, uint32_t max);
WildEncounter **generate_H2_encounter_array(Player pl, AreaEntry aEntry, GameVersion gv, uint16_t seed, uint32_t init, uint32_t max);
WildEncounter **generate_H4_encounter_array(Player pl, AreaEntry aEntry, GameVersion gv, uint16_t seed, uint32_t init, uint32_t max);

#endif