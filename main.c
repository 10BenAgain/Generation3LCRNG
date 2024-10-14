#include <stdio.h>
#include <stdint.h>
#include "src/rng.h"
#include "src/pokemon.h"
#include "src/generator.h"

int main() {
    Player player;
    Static_e encounter;
    uint32_t max;
    uint32_t seed;

    printf("Enter TID: \n");
    scanf("%d", &player.TID);

    printf("Enter SID: \n");
    scanf("%d", &player.SID);

    encounter.pl = player;

    printf("Enter max advance: \n");
    scanf("%d", &max);

    printf("Enter staring seed: \n");
    scanf("%X", &seed);

    printf("Enter pokemon number to generate: \n");
    scanf("%d", &encounter.mon);
    
    generate_static_encounter(encounter, seed, 0, max);

    return 0;
}