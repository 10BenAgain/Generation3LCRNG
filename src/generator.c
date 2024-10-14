#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

// Creates an array of pointers to static encounter structs
Static_e **generate_encounter_array(Player pl, uint16_t mon, uint16_t seed, uint32_t init, uint32_t max) {
    if (max <= 0)
        return NULL;

    uint32_t advances, current_seed;
    advances = max - init;
    if (advances <= 0)
        return NULL;

    // Allocates n memory blocks where n is the amount of advances requested
    Static_e **encounters = (Static_e**)calloc(advances, sizeof(Static_e *));

    // Make sure it actually worked
    if (encounters == NULL) {
        return NULL;
    }

    current_seed = seed;
    int i, j;
    for (i = 0; i <= (int)advances; i++) {
        encounters[i] = (Static_e *)malloc(sizeof(Static_e));
        // If malloc didn't work, then free everything we have allocated already
        if (encounters[i] == NULL) {
            for (j = 0; j < i; j++)
                free(encounters[j]);
            free(encounters);
            return NULL;
        }
        // Mon might not be necessary right now
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
        current_seed = next_seed(&current_seed);
    }
    return encounters;
}