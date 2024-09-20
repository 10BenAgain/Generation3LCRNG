#include <stdio.h>
#include <stdint.h>
// https://www.smogon.com/ingame/rng/pid_iv_creation#example

#define MULTIPLIER 0x41C64E6D
#define INCREMENT 0x6073
#define MOD 4294967295 //2^32

/* Found by calculating the modular multiplicative inverse of the LCRNG prime numbers
 * We know that Next Seed = (a * Last Seed + C) % m
 * Where m is the modulus (2^32)
 * a is the multiplier (0x41C64E6D)
 * c is the increment (0x6073)
 * Using the extended Euclidean algorithm we can say that ax + by = gcd(a,b)
 * 0x4702CBA * (2^32 + 1) + -289805467 * 0x41C64E6D = 1
 * Since gcd(a, b) in this case is 1, we can use ax = 1 (mod m) to calculate the inverse
 * It becomes the value we need to multiply the multiplier by so that the remainder of that number divided by mod m is 1
*/

#define AINVERSE 0xEEB9EB65
#define CINVERSE 0xA3561A1
#define IV_MASK 0x1F
#define IV_SHIFT 5

void increment_seed(uint32_t *seed, uint32_t advances);
void decrement_seed(uint32_t *seed, uint32_t advances);
void decrement_seed_no_inv(uint32_t *seed, uint32_t advances);
void check_seed(uint32_t *seed);
void method1_generate(uint32_t *seed, uint32_t advances, uint32_t *PID, uint8_t *nature, uint8_t *ability, uint8_t *IVs);

const char* get_nature_str(int key);
int is_shiny(uint32_t PID, uint32_t TID, uint32_t SID);

const char* shiny_types[] = {"None", "Star", "Square"};

int main() {
    uint32_t adv = 66444;
    uint32_t init_seed = 0x6942;
    uint32_t PID;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];
    uint32_t TID = 34437;
    uint32_t SID = 44782;

    method1_generate(&init_seed, adv, &PID, &nature, &ability, IVs);
    int shiny = is_shiny(PID, TID, SID);


    printf("PID: %X\n", PID);
    printf("Nature: %s\n", get_nature_str(nature));
    printf("Ability value: %X\n", ability);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", IVs[i]);
    }

    printf("\nIs shiny? : %s", shiny_types[shiny]);
    return 0;
}

void method1_generate(uint32_t *seed, uint32_t advances, uint32_t *PID, uint8_t *nature, uint8_t *ability, uint8_t *IVs) {
    increment_seed(seed, advances + 1);

    uint32_t second_half = *seed >> 16;
    increment_seed(seed, 1);
    uint32_t first_half = *seed >> 16;

    *PID = (first_half << 16) | second_half;

    increment_seed(seed, 1);
    // seed >> 16 this is how the rng just works in gen3
    // Mask result by 31 to ge the first 5 bits of the seed
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

void increment_seed(uint32_t *seed, uint32_t advances) {
    while(advances--)
        *seed = (*seed * MULTIPLIER + INCREMENT) % MOD;
}

void decrement_seed(uint32_t *seed, uint32_t advances) {
    while(advances--)
        *seed = (AINVERSE * *seed + CINVERSE) % MOD;
}

void decrement_seed_no_inv(uint32_t *seed, uint32_t advances) {
    while(advances--)
        *seed = (AINVERSE * (*seed - INCREMENT)) % MOD;
}

typedef struct {
    int key;
    const char *name;
} Nature;

typedef enum {
    MaleOnly    = 0,
    FemaleOnly  = 1,
    Unknown     = 3,
    F1M7        = 0x1F,
    F1M3        = 0x40,
    F1M1        = 0x1A,
    F3M1        = 0x40,
    F7M1        = 0x1F,
} GenderRatio;

Nature natures[] = {
        {0,     "Hardy"     },
        {1,     "Lonely"    },
        {2,     "Brave"     },
        {3,     "Adamant"   },
        {4,     "Naughty"   },
        {5,     "Bold"      },
        {6,     "Docile"    },
        {7,     "Relaxed"   },
        {8,     "Impish"    },
        {9,     "Lax"       },
        {10,    "Timid"     },
        {11,    "Hasty"     },
        {12,    "Serious"   },
        {13,    "Jolly"     },
        {14,    "Naive"     },
        {15,    "Modest"    },
        {16,    "Mild"      },
        {17,    "Quiet"     },
        {18,    "Bashful"   },
        {19,    "Rash"      },
        {20,    "Calm"      },
        {21,    "Gentle"    },
        {22,    "Sassy"     },
        {23,    "Careful"   },
        {24,    "Quirky"    }
};

typedef struct {
    uint32_t dex;
    const char* name;
    uint8_t base_IVs[6];
    GenderRatio gr;
} Pokemon;

Pokemon pokemon[152] = {
        {1, "Bulbasaur", {45, 49, 49, 65, 65, 45}, F1M7},
};

const char* get_nature_str(int key) {
    if (key > sizeof(natures)/sizeof(natures[0])){
        return "Huh?!";
    }
    return natures[key].name;
}

int is_shiny(uint32_t PID, uint32_t TID, uint32_t SID) {
    uint16_t psv = (TID ^ SID) ^ (PID >> 16) ^ (PID & 0xFFFF);

    if (psv == 0)
        return 2;
    else if (psv < 8)
        return 1;
    else
        return 0;
}


// Probably a very roundabout way of calculating the inverse C
void check_seed(uint32_t *seed) {
    printf("Current seed: %X\n", *seed);
    unsigned int check = *seed;
    *seed = (AINVERSE * *seed) % MOD;
    decrement_seed_no_inv(&check, 1);
    printf("Seed decreased by one advance without C: %X\n", *seed);
    printf("Seed decreased by on with C: %X\n", check);
    printf("Difference 0x%X = inverse additive value", (check - *seed));
}


