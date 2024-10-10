#include <stdio.h>
#include <stdint.h>
#include "src/rng.h"
#include "src/pokemon.h"

int main() {
    uint32_t adv = 80682;
    uint32_t init_seed = 0xEE59;
    uint32_t PID;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];
    uint32_t TID = 34437;
    uint32_t SID = 44782;

    method1_generate(&init_seed, adv, &PID, &nature, &ability, IVs);
    int shiny = is_shiny(PID, TID, SID);

    if (shiny) {
        printf("PID: %X |  ", PID);
        printf("Nature: %s |  ", get_nature_str(nature));
        printf("Ability value: %X |  ", ability);

        for (int j = 0; j < 6; j++) {
            printf("%d  ", IVs[j]);
        }
    }
    printf("| Is shiny? : %s | \n", shiny_types[shiny]);

    return 0;
}