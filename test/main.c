#include <stdio.h>
#include <stdint.h>

#define MULTIPLIER  0x41C64E6D
#define INCREMENT   0x6073
#define MOD         4294967295 //2^32
#define AINVERSE    0xEEB9EB65

int
get_unown_shape(uint32_t PID) {
    return (
        ((PID & 0x3000000) >> 18) | 
        ((PID & 0x30000) >> 12) | 
        ((PID & 0x300) >> 6) | 
        (PID & 0x3)) % 28;
}

char 
unown_symbols(int val) {
    if (val > 25) {
        switch (val) {
            case 26:
                return '!';
            case 27:
                return '?';
            default:
                return '$';
        }
    } else
        return (char)(val + 65);
}

void 
increment_seed(uint32_t *seed, uint32_t advances) {
    while(advances--)
        *seed = (*seed * MULTIPLIER + INCREMENT) % MOD;
}

uint16_t 
nextUShort(uint16_t max, uint32_t seed) {
    increment_seed(&seed, 1);
    uint16_t rand = seed >> 16;
    return rand % max;
}

// https://github.com/pret/pokefirered/blob/master/src/data/wild_encounters.json

static const uint8_t 
grass_encounter_slot_lookup_table[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 
    7, 7, 7, 7, 7, 
    8, 8, 8, 8,
    9, 9, 9, 9,
    10,
    11
};

static const uint8_t
water_enctounter_slot_lookup_table[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2,
    3, 3, 3, 3,
    4
};

static const uint8_t
rock_smash_encounter_lookup_table[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2,
    3, 3, 3, 3,
    4
};

static const uint8_t
old_rod_encounter_lookup_table[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

static const uint8_t
good_rod_encounter_lookup_table[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

static const uint8_t
super_rod_encounter_lookup_table[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3,
    4
};

int main() {
    uint32_t s;
    s = 0xEE53;
    uint32_t *p_s;
    p_s = &s;

    printf("Starting seed: %X\n", s);

    increment_seed(p_s, 182);

    uint16_t enc_val;
    enc_val = nextUShort(100, s);
    printf("After 100 advances: %X\n", *p_s);
    printf("Next U Short 100 = %d\n", enc_val);
    printf("Lookup grass encounter slot %d\n", grass_encounter_slot_lookup_table[enc_val]);
    return 0;
}