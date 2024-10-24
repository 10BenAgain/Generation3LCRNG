#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "include/pokemon.h"
#include "include/generator.h"
#include "include/ivs.h"
#include "include/seeds.h"
#include "include/rng.h"

void generate_m1_results();

int main() {
    Player pl;
    AreaEntry aEntry;
    GameVersion gv;
    uint16_t seed;
    uint32_t init;
    uint32_t max;

    pl.TID = 34437;
    pl.SID = 44782;
    aEntry = waterAreaMap[6];
    gv = LG;
    seed = 0xEE53;
    init = 50;
    max = 100;

    WildEncounter **encs = generate_H4_encounter_array(pl, aEntry, gv, seed, init, max);

    if (encs == NULL) {
        printf("Memory allocation failed \n");
        return 1;
    }

    int i, j;
    for (i = 0; i < (int)(max - init); i++) {
        Pokemon mon = pokemon[encs[i]->mon];
        const char * ability;
        if (encs[i]->ability) {
            ability = mon.ab1;
        }
        else {
            ability = mon.ab0;
        }

        printf("%d | ", i + init);
        printf("Slot: %d |", encs[i]->slot);
        printf("%s |", mon.name);
        printf("%d |", encs[i]->level);
        printf("%X | ", encs[i]->PID);
        printf("%s | " , get_nature_str(encs[i]->nature));
        printf("% d: %s |", encs[i]->ability, ability);
        for (j = 0; j < 6; j++) {
            printf("%d  ", encs[i]->IVs[j]);
        }
        printf("| %s ", shiny_types[encs[i]->shiny]);
        printf("| %s ", encs[i]->hp);
        printf("| %d ", encs[i]->hp_pow);

        printf("| %s \n", get_gender_str(get_gender(encs[i]->PID, mon.gr)));
    }

    for (i = 0; i < (int)(max - init); i++) {
        free(encs[i]);
    }

    free(encs);

    return 0;
}

void
generate_m1_results() {
    Player player;
    uint32_t max;
    uint32_t seed;
    uint16_t mon;

    printf("Enter TID: \n");
    scanf("%d", &player.TID);

    printf("Enter SID: \n");
    scanf("%d", &player.SID);

    printf("Enter max advance: \n");
    scanf("%d", &max);

    printf("Enter staring seed: \n");
    scanf("%X", &seed);

    printf("Enter pokemon number to generate: \n");
    scanf("%hd", &mon);

    StaticEncounter **encs = generate_M1_encounter_array(player, mon, seed, 0, max);

    if (encs == NULL) {
        printf("Memory allocation failed \n");
        return;
    }

    int i, j;
    for (i = 0; i < (int)max; i++) {
        printf("%d | ", i);
        printf("%X | ", encs[i]->PID);
        printf("%s | " , get_nature_str(encs[i]->nature));
        printf("Ability: %X |", encs[i]->ability);
        for (j = 0; j < 6; j++) {
            printf("%d  ", encs[i]->IVs[j]);
        }
        printf("| %s ", shiny_types[encs[i]->shiny]);
        printf("| %s ", encs[i]->hp);
        printf("| %d ", encs[i]->hp_pow);
        printf("| %s \n", encs[i]->gender);
    }

    for (i = 0; i < (int)max; i++) {
        free(encs[i]);
    }

    free(encs);
}