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

 void
 method_h4_generate(
         uint32_t seed,
         uint32_t *PID,
         EncounterType et,
         Slot *slt,
         uint8_t *mon,
         uint8_t *encS,
         uint8_t *level,
         uint8_t *nature,
         uint8_t *ability,
         uint8_t *IVs) {

     uint32_t current_seed;
     current_seed = seed;

     *encS = get_enc_table(et)[nextUShort(100, current_seed)];
     increment_seed(&current_seed, 1);

     *level = calculate_level(slt[*encS], current_seed);
     *mon = slt[*encS].mon;

     increment_seed(&current_seed, 1); // Level Advance

     // Tanoby ruins will need to be added to calculation here as well

     increment_seed(&current_seed, 1);
     *nature = (current_seed >> 16) % 25;
     do
     {
         // PID re-roll https://docs.google.com/spreadsheets/d/1hCZznFa4cez3l2qx1DmYPbuB_dNGTqqCoaksZf-Q44s/edit?usp=sharing
         increment_seed(&current_seed, 1);
         uint32_t second_half = current_seed >> 16;
         increment_seed(&current_seed, 1);
         uint32_t first_half = current_seed >> 16;
         *PID = (first_half << 16) | second_half;
    } while (*PID % 25 != *nature);

     *ability = *PID & 1;

     increment_seed(&current_seed, 1);
     // seed >> 16 this is how the rng just works in gen3
     // Mask result by 31 to get the first 5 bits of the seed
     // Each prior shift is the following stat
     IVs[0] = (current_seed >> 16) & IV_MASK; // HP
     IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
     IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

     // Move RNG by two due to vblank in between IV generation
     increment_seed(&current_seed, 2);
     IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
     IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
     IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe
 }

void
method_h2_generate(
        uint32_t seed,
        uint32_t *PID,
        EncounterType et,
        Slot *slt,
        uint8_t *mon,
        uint8_t *encS,
        uint8_t *level,
        uint8_t *nature,
        uint8_t *ability,
        uint8_t *IVs) {

    uint32_t current_seed;
    current_seed = seed;

    *encS = get_enc_table(et)[nextUShort(100, current_seed)];
    increment_seed(&current_seed, 1);

    *level = calculate_level(slt[*encS], current_seed);
    *mon = slt[*encS].mon;

    increment_seed(&current_seed, 1); // Level Advance

    // Tanoby ruins will need to be added to calculation here as well

    increment_seed(&current_seed, 1);
    *nature = (current_seed >> 16) % 25;

    do
    {
        // PID re-roll https://docs.google.com/spreadsheets/d/1hCZznFa4cez3l2qx1DmYPbuB_dNGTqqCoaksZf-Q44s/edit?usp=sharing
        increment_seed(&current_seed, 1);
        uint32_t second_half = current_seed >> 16;
        increment_seed(&current_seed, 1);
        uint32_t first_half = current_seed >> 16;
        *PID = (first_half << 16) | second_half;
    } while (*PID % 25 != *nature);

    *ability = *PID & 1;

    // RNG Advances by two due to vblank before IV generation
    increment_seed(&current_seed, 2);
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
}

void
method_h1_generate(
        uint32_t seed,
        uint32_t *PID,
        EncounterType et,
        Slot *slt,
        uint8_t *mon,
        uint8_t *encS,
        uint8_t *level,
        uint8_t *nature,
        uint8_t *ability,
        uint8_t *IVs) {

    uint32_t current_seed;
    current_seed = seed;

    *encS = get_enc_table(et)[nextUShort(100, current_seed)];
    increment_seed(&current_seed, 1);

    *level = calculate_level(slt[*encS], current_seed);
    *mon = slt[*encS].mon;

    increment_seed(&current_seed, 1); // Level Advance

    // Tanoby ruins will need to be added to calculation here as well

    increment_seed(&current_seed, 1);
    *nature = (current_seed >> 16) % 25;
    do
    {
        // PID re-roll https://docs.google.com/spreadsheets/d/1hCZznFa4cez3l2qx1DmYPbuB_dNGTqqCoaksZf-Q44s/edit?usp=sharing
        increment_seed(&current_seed, 1);
        uint32_t second_half = current_seed >> 16;

        increment_seed(&current_seed, 1);
        uint32_t first_half = current_seed >> 16;

        *PID = (first_half << 16) | second_half;
    } while (*PID % 25 != *nature);

    *ability = *PID & 1;

    // No Vblanks compared to H2/H4
    // RNG Advances by one
    increment_seed(&current_seed, 1);
    // seed >> 16 this is how the rng just works in gen3
    // Mask result by 31 to get the first 5 bits of the seed
    // Each prior shift is the following stat
    IVs[0] = (current_seed >> 16) & IV_MASK; // HP
    IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
    IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

    increment_seed(&current_seed, 1);
    IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
    IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
    IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe
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

uint8_t
calculate_level(Slot s, uint32_t seed) {
    uint8_t range = s.maxL - s.minL + 1;
    uint8_t next = nextUShort(range, seed);
    return s.minL + next;
}

uint32_t 
next_seed(const uint32_t *seed) {
    return (*seed * MULTIPLIER + INCREMENT) % MOD;
}

uint16_t 
nextUShort(uint16_t max, uint32_t seed) {
    increment_seed(&seed, 1);
    uint16_t rand = seed >> 16;
    return rand % max;
}

/*
    *  jump[1].add = 0x6073 * 0x41C64E6D + 1 = 0x6073 * 0x41C64E6E = 0x18C7E97E7B6A & 0xFFFFFFF (uint32_t cast) = 0xE97E7B6A
    *  jump[1].multiplier = 0x41C64E6D * 0x41C64E6D = 0x10E64D70C2A29A69 & 0xFFFFFFF = 0xC2A29A69
    *
    *  Jump[1] Add = 0xE97E7B6A
    *  Jump[1] Multiplier = 0xC2A29A69
    *
    *  Jump[2].add = Jump[1] Add * (Jump[1] Multiplier + 1) = 0xE97E7B6A * 0xC2A29A6A = 0xB186286731B0DDE4 & 0xFFFFFFFF = 0x31B0DDE4
    *  Jump[2].multiplier = Jump[1] Multiplier * Jump[1] Multiplier = 0x93FAD94EEE067F11 & 0xFFFFFFFF = 0xEE067F11
    *
    *  Jump[2] Add = 0x31B0DDE4
    *  Jump[2] Multiplier = 0xEE067F11
    *
    *  Etc..
*/

// https://github.com/Admiral-Fish/PokeFinder/blob/a0c55aec852618a4afff3116b48b3e7df7ba07df/Source/Core/RNG/LCRNG.cpp#L20-L36
JumpTable
*compute_jump_table() {
    JumpTable *jt = malloc(sizeof(JumpTable));
    jt->jump[0].add = INCREMENT;
    jt->jump[0].multiplier = MULTIPLIER;

    for ( size_t i = 1; i < 32; i++) {
        jt->jump[i].add = jt->jump[i - 1].add * (jt->jump[i - 1].multiplier + 1);
        jt->jump[i].multiplier = jt->jump[i - 1].multiplier * jt->jump[i - 1].multiplier;
    }
    return jt;
}

/*
* Seed = 0xEE53, i = 0, Advances = 10 | Advances & 1 = 0 | Then 10 >>= 1 = 8, etc..
* Once i = 3, then (advances & 1) is True
* Then seed = ( 0xEE53 * 0xCFDDDF21 + 0x67DBB608 ) = 0xD542F91D
*/
uint32_t
jump_ahead(const Jump table[32], uint32_t seed, uint32_t advances) {
    int i;
    for (i = 0; advances; advances >>= 1, i++) {
        if (advances & 1) {
            seed = seed * table[i].multiplier + table[i].add;
        }
    }
    return seed;
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
