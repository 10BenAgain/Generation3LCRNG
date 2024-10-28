#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "include/pokemon.h"
#include "include/generator.h"
#include "include/ivs.h"
#include "include/seeds.h"
#include "include/rng.h"
#include "include/filters.h"

int main() {
    Player player;
    uint32_t init, max;
    uint32_t seed;
    uint16_t mon;

    wenc_node *head = NULL;
    player.SID = 34437;
    player.TID = 44872;
    init = 0;
    max = 10000000;
    seed = 0xEE53;
    mon = 0;
    AreaEntry at = landAreaMap[55];

    clock_t t;
    t = clock();
    generateWildEncounter(&head, player, H1, at, LG, seed, init, max);
    print_wencounter_list(head);
    t = clock() - t;
    double time_taken = (double)t/CLOCKS_PER_SEC;
    printf("Completed in %f seconds", time_taken);
    freeWEncList(head);

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