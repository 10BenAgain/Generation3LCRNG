#include "locations.h"

const char
*get_enc_path(const char *folder, const char* file) {
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

const char
*get_encounter_file_path(GameVersion gv, AreaType at) {
    char *LGpath = "data/LGENCSLOTS/";
    char *FRpath = "data/FRENCSLOTS/";
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
    for (size_t i = 0; i < sizeof(encMappings) / sizeof(EncounterFileMap); i++) {
        if (encMappings[i].at == at) {
            file = encMappings[i].fn;
            break;
        }
    }
    return get_enc_path(path, file);
}

Slot
*load_slots(AreaEntry area, const char *fn) {
    FILE *fp = NULL;
    fp = fopen(fn, "r");
    if (fp == NULL) return NULL;

    size_t max_line_size = MAX_LEVEL_LENGTH * SLOTS_COUNT + MAX_MON_LENGTH * SLOTS_COUNT + SLOTS_COUNT + 10;
    char line[max_line_size];
    int c, i, s;

    c = 0;
    while(fgets(line, sizeof(line), fp)) {
        if (c == area.index) {
            break;
        }
        c++;
    }

    if (c != area.index) {
        fclose(fp);
        return NULL;
    }

    Slot *slots = malloc(SLOTS_COUNT * sizeof(Slot));
    if (slots == NULL) return NULL;
    char *token = strtok(line, ",");

    switch(area.at) {
        case LAND:
            s = LAND_SLOTS;
            break;
        case WATER:
        case ROCKSMASH:
            s = ROCK_SLOTS;
            break;
        default:
            return NULL;
    }

    i = 0;
    while(token != NULL && i < s) {
        slots[i].index = (uint8_t)atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            slots[i].mon = (uint8_t)atoi(token);
        }
        token = strtok(NULL, ",");
        if (token != NULL) {
            slots[i].minL = (uint8_t)atoi(token);
        }
        if (s == LAND_SLOTS) {
            slots[i].maxL = (uint8_t)atoi(token);
        }
        else {
            token = strtok(NULL, ",");
            if (token != NULL) {
                slots[i].maxL = (uint8_t)atoi(token);
            }
        }
        i++;
        token = strtok(NULL, ",");
    }
    return slots;
}