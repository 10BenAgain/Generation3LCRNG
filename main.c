#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "src/pokemon.h"
#include "src/generator.h"

void generate_m1_results();

int main() {

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

    Static_e **encs = generate_encounter_array(player, mon, seed, 0, max);

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