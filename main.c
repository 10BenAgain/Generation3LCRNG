#include <stdio.h>
#include <stdint.h>
#include "src/rng.h"
#include "src/pokemon.h"

int main() {
    uint32_t PID;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];

    uint32_t adv;
    uint32_t init_seed;
    uint32_t TID;
    uint32_t SID;

    printf("Enter TID: \n");
    scanf("%d", &TID);

    printf("Enter SID: \n");
    scanf("%d", &SID);

    printf("Enter max advance: \n");
    scanf("%d", &adv);

    printf("Enter staring seed: \n");
    scanf("%X", &init_seed);

    uint32_t init_copy;
    init_copy = init_seed;
    
    uint32_t i, j;
    for (i = 0; i < adv; i++) {
        method1_generate(&init_seed, i, &PID, &nature, &ability, IVs);
        int shiny = is_shiny(PID, TID, SID);

        if (shiny) {
            printf("%d  |", i);
            printf("%X |  ", PID);
            printf("%s |  ", get_nature_str(nature));
            printf("Ability: %X |  ", ability);

            for (j = 0; j < 6; j++) {
                printf("%d  ", IVs[j]);
            }

            printf("| %s", shiny_types[shiny]);
            printf("| %s : %d | ", HP[get_hp_value(IVs)].type, get_hp_power(IVs));
            printf("Gender: %d\n",get_gender(PID, pokemon[1].gr));
        }
        init_seed = init_copy;
    }

    return 0;
}