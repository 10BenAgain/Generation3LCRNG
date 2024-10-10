#include "rng.h"

void 
method1_generate(uint32_t *seed, uint32_t advances, uint32_t *PID, uint8_t *nature, uint8_t *ability, uint8_t *IVs) {
    increment_seed(seed, advances + 1);

    uint32_t second_half = *seed >> 16;
    increment_seed(seed, 1);
    uint32_t first_half = *seed >> 16;

    *PID = (first_half << 16) | second_half;

    increment_seed(seed, 1);
    // seed >> 16 this is how the rng just works in gen3
    // Mask result by 31 to get the first 5 bits of the seed
    // Each prior shift is the following stat
    IVs[0] = (*seed >> 16) & IV_MASK; // HP
    IVs[1] = ((*seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
    IVs[2] = ((*seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

    // Move RNG by one
    increment_seed(seed, 1);
    IVs[5] = (*seed >> 16) & IV_MASK; // SpA
    IVs[3] = ((*seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
    IVs[4] = ((*seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe

    *nature = *PID % 25;
    *ability = *PID & 1;
}

void 
increment_seed(uint32_t *seed, uint32_t advances) {
    while(advances--)
        *seed = (*seed * MULTIPLIER + INCREMENT) % MOD;
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
