#include <stdlib.h>
#include "generator.h"

// Creates an array of pointers to static encounter structs
StaticEncounter
**generate_M1_encounter_array(Player pl, uint16_t mon, uint16_t seed, uint32_t init, uint32_t max) {
    if (max <= 0)
        return NULL;

    uint32_t advances, current_seed;
    advances = max - init;
    if (advances <= 0)
        return NULL;

    // Allocates n memory blocks where n is the amount of advances requested
    StaticEncounter **encounters = (StaticEncounter**)calloc(advances, sizeof(StaticEncounter *));

    // Make sure it actually worked
    if (encounters == NULL) {
        return NULL;
    }

    current_seed = jump_ahead(Gen3JumpTable, seed, advances);
    int i, j;
    for (i = 0; i <= (int)advances; i++, increment_seed(&current_seed, 1)) {
        encounters[i] = (StaticEncounter *)malloc(sizeof(StaticEncounter));
        // If malloc didn't work, then free everything we have allocated already
        if (encounters[i] == NULL) {
            for (j = 0; j < i; j++)
                free(encounters[j]);
            free(encounters);
            return NULL;
        }
        encounters[i]->mon = mon;
        method1_generate(
            current_seed,
            &encounters[i]->PID,
            &encounters[i]->nature,
            &encounters[i]->ability,
            encounters[i]->IVs
        );
        encounters[i]->shiny = is_shiny(encounters[i]->PID, pl.TID, pl.SID);
        encounters[i]->gender = get_gender_str(get_gender(encounters[i]->PID, pokemon[mon].gr));
        encounters[i]->hp = HP[get_hp_value(encounters[i]->IVs)].type;
        encounters[i]->hp_pow = get_hp_power(encounters[i]->IVs);
    }
    return encounters;
}

WildEncounter **generate_H1_encounter_array(Player pl, AreaEntry aEntry, GameVersion gv, uint16_t seed, uint32_t init, uint32_t max) {
    if (max <= 0)
        return NULL;

    uint32_t advances, current_seed;
    advances = max - init;
    if (advances <= 0)
        return NULL;

    // Allocates n memory blocks where n is the amount of advances requested
    WildEncounter **encounters = (WildEncounter**)calloc(advances, sizeof(WildEncounter *));

    // Make sure it actually worked
    if (encounters == NULL) {
        return NULL;
    }

    const char *encounter_data_path = get_encounter_file_path(gv, aEntry.at);
    Slot *slots = load_slots(aEntry, encounter_data_path);
    if (slots == NULL) {
        free(slots);
        return NULL;
    }

    EncounterType et = area2enc(aEntry.at);
    current_seed = jump_ahead(Gen3JumpTable, seed, advances);
    int i, j;
    for (i = 0; i <= (int)advances; i++, increment_seed(&current_seed, 1)) {
        encounters[i] = (WildEncounter *) malloc(sizeof(WildEncounter));
        // If malloc didn't work, then free everything we have allocated already
        if (encounters[i] == NULL) {
            for (j = 0; j < i; j++)
                free(encounters[j]);
            free(encounters);
            return NULL;
        }
        method_h1_generate(
                current_seed,
                &encounters[i]->PID,
                et,
                slots,
                &encounters[i]->mon,
                &encounters[i]->slot,
                &encounters[i]->level,
                &encounters[i]->nature,
                &encounters[i]->ability,
                encounters[i]->IVs
        );
        encounters[i]->shiny = is_shiny(encounters[i]->PID, pl.TID, pl.SID);
        encounters[i]->hp = HP[get_hp_value(encounters[i]->IVs)].type;
        encounters[i]->hp_pow = get_hp_power(encounters[i]->IVs);
    }
    return encounters;
}

WildEncounter **generate_H2_encounter_array(Player pl, AreaEntry aEntry, GameVersion gv, uint16_t seed, uint32_t init, uint32_t max) {
    if (max <= 0)
        return NULL;

    uint32_t advances, current_seed;
    advances = max - init;
    if (advances <= 0)
        return NULL;

    // Allocates n memory blocks where n is the amount of advances requested
    WildEncounter **encounters = (WildEncounter**)calloc(advances, sizeof(WildEncounter *));

    // Make sure it actually worked
    if (encounters == NULL) {
        return NULL;
    }

    const char *encounter_data_path = get_encounter_file_path(gv, aEntry.at);
    Slot *slots = load_slots(aEntry, encounter_data_path);
    if (slots == NULL) {
        free(slots);
        return NULL;
    }

    EncounterType et = area2enc(aEntry.at);
    current_seed = jump_ahead(Gen3JumpTable, seed, advances);
    int i, j;
    for (i = 0; i <= (int)advances; i++, increment_seed(&current_seed, 1)) {
        encounters[i] = (WildEncounter *) malloc(sizeof(WildEncounter));
        // If malloc didn't work, then free everything we have allocated already
        if (encounters[i] == NULL) {
            for (j = 0; j < i; j++)
                free(encounters[j]);
            free(encounters);
            return NULL;
        }
        method_h2_generate(
                current_seed,
                &encounters[i]->PID,
                et,
                slots,
                &encounters[i]->mon,
                &encounters[i]->slot,
                &encounters[i]->level,
                &encounters[i]->nature,
                &encounters[i]->ability,
                encounters[i]->IVs
        );
        encounters[i]->shiny = is_shiny(encounters[i]->PID, pl.TID, pl.SID);
        encounters[i]->hp = HP[get_hp_value(encounters[i]->IVs)].type;
        encounters[i]->hp_pow = get_hp_power(encounters[i]->IVs);
    }
    return encounters;
}

WildEncounter **generate_H4_encounter_array(Player pl, AreaEntry aEntry, GameVersion gv, uint16_t seed, uint32_t init, uint32_t max) {
    if (max <= 0)
        return NULL;

    uint32_t advances, current_seed;
    advances = max - init;
    if (advances <= 0)
        return NULL;

    // Allocates n memory blocks where n is the amount of advances requested
    WildEncounter **encounters = (WildEncounter**)calloc(advances, sizeof(WildEncounter *));

    // Make sure it actually worked
    if (encounters == NULL) {
        return NULL;
    }

    const char *encounter_data_path = get_encounter_file_path(gv, aEntry.at);
    Slot *slots = load_slots(aEntry, encounter_data_path);
    if (slots == NULL) {
        free(slots);
        return NULL;
    }

    EncounterType et = area2enc(aEntry.at);
    current_seed = jump_ahead(Gen3JumpTable, seed, init);
    int i, j;
    for (i = 0; i <= (int)advances; i++, increment_seed(&current_seed, 1)) {
        encounters[i] = (WildEncounter *) malloc(sizeof(WildEncounter));
        // If malloc didn't work, then free everything we have allocated already
        if (encounters[i] == NULL) {
            for (j = 0; j < i; j++)
                free(encounters[j]);
            free(encounters);
            return NULL;
        }
        method_h4_generate(
                current_seed,
                &encounters[i]->PID,
                et,
                slots,
                &encounters[i]->mon,
                &encounters[i]->slot,
                &encounters[i]->level,
                &encounters[i]->nature,
                &encounters[i]->ability,
                encounters[i]->IVs
        );
        encounters[i]->shiny = is_shiny(encounters[i]->PID, pl.TID, pl.SID);
        encounters[i]->hp = HP[get_hp_value(encounters[i]->IVs)].type;
        encounters[i]->hp_pow = get_hp_power(encounters[i]->IVs);
    }
    return encounters;
}