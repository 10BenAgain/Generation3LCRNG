#ifndef SEEDS_H
#define SEEDS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    STEREO,
    MONO
} AudioSetting;

typedef enum {
    LA,
    HELP,
    LR
} ButtonSetting;

typedef enum {
    A,
    START,
    L
} ButtonSeed;

typedef enum {
    FR,
    LG
} GameVersion;

typedef struct {
    uint32_t timer;
    uint16_t seed;
} InitialSeed;


typedef struct {
    AudioSetting audS;
    ButtonSetting btnS;
    ButtonSeed btn;
    const char *file;
} OptionFileMap;


#define MAX_TIMER_LENGTH 10
#define MAX_SEED_LENGTH 10

const char *get_seed_file_path(GameVersion gv, AudioSetting audS, ButtonSetting btnS, ButtonSeed btn);
InitialSeed *load_initial_seeds(const char *fn, uint64_t *len);

#endif
