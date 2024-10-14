#include "generator.h"

void 
generate_static_encounter(Static_e enc, uint16_t seed, uint32_t init, uint32_t max ) {
    uint32_t current_seed, advance;
    current_seed = seed;
    advance = max - init;

    int i, j;
    for (i = 0; i <= (int)advance; i++) {
        method1_generate(
            current_seed,
            &enc.PID,
            &enc.nature,
            &enc.ability,
            enc.IVs
        );
        enc.shiny = is_shiny(enc.PID, enc.pl.TID, enc.pl.SID);
        enc.gender = get_gender_str(get_gender(enc.PID, pokemon[enc.mon].gr));
        enc.hp = HP[get_hp_value(enc.IVs)].type;
        enc.hp_pow = get_hp_power(enc.IVs);

        printf("%d | ", i);
        printf("%X | ", enc.PID);
        printf("%s | " , get_nature_str(enc.nature));
        printf("Ability: %X |", enc.ability);
        for (j = 0; j < 6; j++) {
                printf("%d  ", enc.IVs[j]);
            }
            
        printf("| %s ", shiny_types[enc.shiny]);
        printf("| %s ", enc.hp);
        printf("| %d ", enc.hp_pow);
        printf("| %s \n", enc.gender);

        current_seed = next_seed(&current_seed);
    }
}