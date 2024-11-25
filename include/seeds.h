#ifndef SEEDS_H
#define SEEDS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "enums.h"

typedef struct {
    uint32_t timer;
    uint32_t seed;
} InitialSeed;

typedef struct {
    AudioSetting audS;
    ButtonSetting btnS;
    ButtonSeed btn;
    const char *file;
} OptionFileMap;

#define MAX_TIMER_LENGTH 10
#define MAX_SEED_LENGTH 10

const char *get_seed_file_path(GameVersion gv, Language lang, JPNVersion jver, AudioSetting audS, ButtonSetting btnS, ButtonSeed btn);
InitialSeed *load_initial_seeds(const char *fn, uint64_t *len, SeedOffset ofs);
intt find_seed_index(InitialSeed *set, uint32_t seed, uint64_t length);
InitialSeed *get_seed_range(InitialSeed *set, uint64_t length, int index, uint16_t range, uint64_t *newLen);

#endif
