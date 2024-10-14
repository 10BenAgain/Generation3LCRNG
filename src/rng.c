#include "rng.h"

void 
method1_generate(uint32_t seed, uint32_t *PID, uint8_t *nature, uint8_t *ability, uint8_t *IVs) {

    uint32_t current_seed;
    current_seed = seed;
    increment_seed(&current_seed, 1);

    uint32_t second_half = current_seed >> 16;
    increment_seed(&current_seed, 1);
    uint32_t first_half = current_seed >> 16;

    *PID = (first_half << 16) | second_half;

    increment_seed(&current_seed, 1);
    // seed >> 16 this is how the rng just works in gen3
    // Mask result by 31 to get the first 5 bits of the seed
    // Each prior shift is the following stat
    IVs[0] = (current_seed >> 16) & IV_MASK; // HP
    IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
    IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

    // Move RNG by one
    increment_seed(&current_seed, 1);
    IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
    IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
    IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe

    *nature = *PID % 25;
    *ability = *PID & 1;
}

// void
// method4_generate(uint32_t seed, uint32_t advances, uint32_t *PID, uint8_t *nature, uint8_t *ability, uint8_t *IVs) {

// }

void 
increment_seed(uint32_t *seed, uint32_t advances) {
    while(advances--)
        *seed = (*seed * MULTIPLIER + INCREMENT) % MOD;
}

uint32_t 
next_seed(uint32_t *seed) {
    return (*seed * MULTIPLIER + INCREMENT) % MOD;
}

void 
decrement_seed(uint32_t *seed, uint32_t advances) {
    while(advances--) {
        // Probably not optimal nor the best way to get back to original seed but hey, it works for now
        if (*seed & 0xFFFF0000)
            *seed = (AINVERSE * *seed + CINVERSE) % MOD;
        else
            break;
    }
}

uint16_t 
nextUShort(uint16_t max, uint32_t seed) {
    increment_seed(&seed, 1);
    uint16_t rand = seed >> 16;
    return rand % max;
}

// Probably a very roundabout way of calculating the inverse C
void 
check_seed(uint32_t *seed) {
    printf("Current seed: %X\n", *seed);
    unsigned int check = *seed;
    *seed = (AINVERSE * *seed) % MOD;
    decrement_seed(&check, 1);
    printf("Seed decreased by one advance without C: %X\n", *seed);
    printf("Seed decreased by on with C: %X\n", check);
    printf("Difference 0x%X = inverse additive value", (check - *seed));
}
