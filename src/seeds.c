#include "seeds.h"

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
    printf("Size of line = %llu\n", sizeof(line));
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



