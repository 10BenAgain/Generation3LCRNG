
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

/*This sucks, but it should work for now until fishing is implemented in V3 OCR shite*/
static EncounterType
area2enc(AreaType at) {
    switch (at) {
        case LAND:
            return Grass;
        case WATER:
            return Water;
        case ROCKSMASH:
            return RockSmash;
        default:
            return Grass;
    }
}
#endif
