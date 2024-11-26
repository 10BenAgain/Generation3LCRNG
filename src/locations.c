#include "../include/locations.h"

const char* EncounterTypeStrings[3] = {
    "Grass",
    "Water",
    "Rock Smash"
};

const char
*get_enc_path(const char *folder, const char* file) {
    char *result = NULL;
    const size_t lfo = strlen(folder);
    const size_t lfd = strlen(file);

    result = malloc(lfo + lfd + 1); // +1 for terminator char

    if (result == NULL) {
        perror("Memory allocation of file path string failed");
        return NULL;
    }

    // Copy folder memory into result with a size of folder string size
    memcpy(result, folder, lfo);

    // Copy file string after into result after the size of folder block
    memcpy(result + lfo, file, lfd + 1);

    return result;
}

const char *get_encounter_file_path(GameVersion gv, AreaType at) {
#ifdef BUILD_PATH
    char *LGpath = "../data/LGENCSLOTS/";
    char *FRpath = "../data/FRENCSLOTS/";
#else
    char *LGpath = "data/LGENCSLOTS/";
    char *FRpath = "data/FRENCSLOTS/";
#endif

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

Slot *load_slots(AreaEntry area, const char *fn) {
    FILE *fp = NULL;
    fp = fopen(fn, "r");
    if (fp == NULL) {
        perror("Unable to open encounter slot file!");
        return NULL;
    }

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
    if (slots == NULL) {
        perror("Memory allocation of encounter slots failed!");
        return NULL;
    }
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

void listMonsInLocation(GameVersion gv, AreaEntry entry) {
    AreaType at = entry.at;
    const char* enc_path = get_encounter_file_path(gv, at);
    Slot* slots = load_slots(entry, enc_path);
    size_t slot_count;
    switch (at) {
        case LAND:
            slot_count = LAND_SLOTS;
            break;
        case WATER:
            slot_count = WATER_SLOTS;
            break;
        case ROCKSMASH:
            slot_count = ROCK_SLOTS;
            break;
    }

    for (size_t i = 0; i < slot_count; i++) {
        fprintf(stdout, "Slot: %d | %s | Level: %d-%d\n",
               slots[i].index, pokemon[slots[i].mon].name, slots[i].minL, slots[i].maxL);
    }

    free(slots);
}

void listLocations(EncounterType et) {
    size_t locations;
    const AreaEntry* map;
    switch (et) {
        case Grass:
            locations = MAPSIZE(landAreaMap);
            map = landAreaMap;
            break;
        case Water:
            locations = MAPSIZE(waterAreaMap);
            map = waterAreaMap;
            break;
        case RockSmash:
            locations = MAPSIZE(rockAreaMap);
            map = rockAreaMap;
            break;
        default:
            return;
    }

    for (size_t i = 0; i < locations; i++) {
        fprintf(stdout, "%d | %s\n", map[i].index, map[i].name);
    }
}