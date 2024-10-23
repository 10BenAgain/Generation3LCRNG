
#ifndef GENERATION3LCRNG_ENUMS_H
#define GENERATION3LCRNG_ENUMS_H

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

typedef enum {
    LAND,
    WATER,
    ROCKSMASH
} AreaType;

typedef enum {
    Grass,
    Water,
    RockSmash,
    OldRod,
    GoodRod,
    SuperRod
} EncounterType;

#endif
