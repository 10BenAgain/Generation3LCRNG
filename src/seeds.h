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

char *LGpath = "data/LG/";
char *FRpath = "data/FR/";

const char optionFiles[14][18] = {
        "Mono-HELP-A",
        "Mono-HELP-Start",
        "Mono-LA-A",
        "Mono-LA-L",
        "Mono-LA-Start",
        "Mono-LR-A",
        "Mono-LR-Start",
        "Stereo-HELP-A",
        "Stereo-HELP-Start",
        "Stereo-LA-A",
        "Stereo-LA-L",
        "Stereo-LA-Start",
        "Stereo-LR-A",
        "Stereo-LR-Start"
};

typedef struct {
    AudioSetting audS;
    ButtonSetting btnS;
    ButtonSeed btn;
    const char *file;
} OptionFileMap;

const OptionFileMap optionFileMappings[] = {
        { MONO,     HELP,   A,      optionFiles[0] },
        { MONO,     HELP,   START,  optionFiles[1] },
        { MONO,     LA,     A,      optionFiles[2] },
        { MONO,     LA,     L,      optionFiles[3] },
        { MONO,     LA,     START,  optionFiles[4] },
        { MONO,     LR,     A,      optionFiles[5] },
        { MONO,     LR,     START,  optionFiles[6] },
        { STEREO,   HELP,   A,      optionFiles[7] },
        { STEREO,   HELP,   START,  optionFiles[8] },
        { STEREO,   LA,     A,      optionFiles[9] },
        { STEREO,   LA,     L,      optionFiles[10] },
        { STEREO,   LA,     START,  optionFiles[11] },
        { STEREO,   LR,     A,      optionFiles[12] },
        { STEREO,   LR,     START,  optionFiles[13] },
};

#define MAX_TIMER_LENGTH 10
#define MAX_SEED_LENGTH 10

InitialSeed *load_initial_seeds(const char *fn, uint64_t *len);

#endif
