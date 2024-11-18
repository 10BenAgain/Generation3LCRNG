#include "../include/rng.h"

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