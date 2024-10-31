#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>
#include <stdint.h>
#include "rng.h"
#include "pokemon.h"
#include "encounter_table.h"
#include "generator.h"
#include "seeds.h"
#include "enums.h"
#include "ivs.h"

typedef struct SNode {
    StaticEncounter se;
    struct SNode* next;
} senc_node;

typedef struct WNode {
    WildEncounter we;
    struct WNode* next;
} wenc_node;

typedef struct {
    uint8_t mon;
    uint8_t level;
    uint8_t ability[2]; // 0 = 0, 1 = 1
    uint8_t hp_iv_bounds[2];
    uint8_t atk_iv_bounds[2];
    uint8_t def_iv_bounds[2];
    uint8_t spa_iv_bounds[2];
    uint8_t spd_iv_bounds[2];
    uint8_t spe_iv_bounds[2];
    uint8_t gender[3]; // 0 = M , 1 = F, 2 = U
    uint8_t shiny[3]; // 0 = Square, 1 = Star, 2 = None
    uint8_t natures[25];
} WildFilter;

void applyNatureToWildFilter(Nature nt, WildFilter* filter);

void applyIVEstimateToWildFilter(IVEstimate* target, WildFilter* filter);

void printSEncounterList(senc_node* enc);
void printWEncounterList(wenc_node* enc);

void freeSEncList(senc_node* head);
void freeWEncList(wenc_node* head);

void generateStaticEncounter(senc_node** list, Player pl, uint16_t mon, uint32_t seed, uint32_t init, uint32_t max);

void generateWildEncounter( wenc_node** list, Player pl, Method met, Slot *slots, EncounterType et, WildFilter filter, uint32_t seed, uint32_t init, uint32_t max);
void generateWildEncountersFromSeedList(wenc_node** list, Player pl, Method met, Slot *slots, EncounterType et, WildFilter filter, InitialSeed *seeds, uint32_t size, uint32_t init, uint32_t max);

#endif
