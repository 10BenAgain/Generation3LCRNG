#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdint.h>
#include "rng.h"
#include "pokemon.h"

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
} Static_e;

Static_e **generate_encounter_array(Player pl, uint16_t mon, uint16_t seed, uint32_t init, uint32_t max);

#endif