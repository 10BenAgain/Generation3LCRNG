#include "../include/seeds.h"

static const char optionFiles[14][18] = {
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

static const OptionFileMap optionFileMappings[] = {
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

// https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
const char
*get_seed_path(const char *folder, const char *file) {
    char *result = NULL;
    const size_t lfo = strlen(folder);
    const size_t lfd = strlen(file);

    result = malloc(lfo + lfd + 1); // +1 for terminator char

    if (result == NULL)
        return NULL;

    // Copy folder memory into result with a size of folder string size
    memcpy(result, folder, lfo);

    // Copy file string after into result after the size of folder block
    memcpy(result + lfo, file, lfd + 1);

    return result;
}

uint64_t
count_lines_in_file(const char *fp) {
    FILE *file = NULL;

    file = fopen(fp, "r");
    if (file == NULL) {
        return 0;
    }
    int count = 0;
    char line[MAX_TIMER_LENGTH + MAX_SEED_LENGTH + 2];

    while(fgets(line, sizeof(line), file)) {
        count ++;
    }
    fclose(file);
    return count;
}

InitialSeed
*load_initial_seeds(const char *fn, uint64_t *len) {
    uint64_t lc = count_lines_in_file(fn);
    if (lc <= 0) return NULL;

    *len = lc;
    InitialSeed *seeds = malloc(lc * sizeof(InitialSeed));
    if (!seeds) {
        free(seeds);
        return NULL;
    }

    FILE *fp;
    fp = fopen(fn, "r");

    if (!fp) {
        free(seeds);
        return NULL;
    }

    uint64_t count = 0;
    char line[MAX_TIMER_LENGTH + MAX_SEED_LENGTH + 2];
    while (fgets(line, sizeof(line), fp) && count < lc) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            seeds[count].timer = (uint32_t)atoi(token);
            token = strtok(NULL, "\n");
            if (token != NULL) {
                seeds[count].seed = (uint16_t)strtol(token, NULL, 16);
                count++;
            }
        }
    }

    fclose(fp);
    return seeds;
}

const char
*get_seed_file_path(GameVersion gv, AudioSetting audS, ButtonSetting btnS, ButtonSeed btn) {
    char *LGpath = "../data/LG/";
    char *FRpath = "../data/FR/";
    const char *path;
    const char *file;

    switch (gv) {
        case FR:
            path = FRpath;
            break;
        case LG:
            path = LGpath;
            break;
        default:
            return NULL;
    }
    for (size_t i = 0; i < sizeof(optionFileMappings) / sizeof(OptionFileMap); i++) {
        if (optionFileMappings[i].audS == audS &&
            optionFileMappings[i].btnS == btnS &&
            optionFileMappings[i].btn == btn) {
            file = optionFileMappings[i].file;
            break;
        }
    }
    return get_seed_path(path, file);
}

/* Linear search is probably bad but w/e */
uint64_t
find_seed_index(InitialSeed *set, uint16_t seed, uint64_t length) {
    if (set == NULL) return 0;

    for (size_t i = 0; i < length; i++) {
        if (set[i].seed == seed) {
            return i;
        }
    }
    return 0;
}

InitialSeed
*get_seed_range(InitialSeed *set, uint16_t length, uint16_t index, uint16_t range, uint64_t *newLen) {
    uint64_t start, end;

    if (index - range > 0) {
        start = index - range;
    } else {
        return NULL;
    }

    if ((index + range) <= length) {
        end = index + range;
    } else {
        return NULL;
    }

    *newLen = end - start;
    InitialSeed *seedR = malloc(*newLen * sizeof(InitialSeed));
    if (seedR == NULL) {
        free(seedR);
        return NULL;
    }
    memcpy(seedR, &set[start], *newLen * sizeof(InitialSeed));
    return seedR;
}



