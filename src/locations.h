#ifndef ENCOUNTERS_H
#define ENCOUNTERS_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "enums.h"

#define MAX_LEVEL_LENGTH    4
#define MAX_MON_LENGTH      4
#define SLOTS_COUNT         12

#define LAND_SLOTS          12
#define ROCK_SLOTS          5
#define WATER_SLOTS         5

typedef struct {
    AreaType at;
    const char *name;
    uint8_t index;
} AreaEntry;

typedef struct {
    uint8_t index;
    uint8_t mon;
    uint8_t minL;
    uint8_t maxL;
} Slot;

typedef struct {
    GameVersion gv;
    AreaType at;
    const char *fn;
} EncounterFileMap;

static const AreaEntry landAreaMap[89] = {
        { LAND, "Altering Cave (Default)", 1 },
        { LAND, "Altering Cave (Mystery Gift)", 2 },
        { LAND, "Altering Cave (Mystery Gift)", 3 },
        { LAND, "Altering Cave (Mystery Gift)", 4 },
        { LAND, "Altering Cave (Mystery Gift)", 5 },
        { LAND, "Altering Cave (Mystery Gift)", 6 },
        { LAND, "Altering Cave (Mystery Gift)", 7 },
        { LAND, "Altering Cave (Mystery Gift)", 8 },
        { LAND, "Altering Cave (Mystery Gift)", 9 },
        { LAND, "Berry Forest ", 10 },
        { LAND, "Bond Bridge", 11 },
        { LAND, "Cape Brink ", 12 },
        { LAND, "Cerulean Cave 1F ", 13 },
        { LAND, "Cerulean Cave 2F ", 14 },
        { LAND, "Cerulean Cave B1F ", 15 },
        { LAND, "Diglett's Cave", 16 },
        { LAND, "Five Isle Meadow", 17 },
        { LAND, "Icefall Cave Entrance", 18 },
        { LAND, "Icefall Cave 1F", 19 },
        { LAND, "Icefall Cave BF", 20 },
        { LAND, "Icefall Cave Back Cavern", 21 },
        { LAND, "Kindle Road", 22 },
        { LAND, "Lost Cave (All Rooms)", 23 },
        { LAND, "Memorial Pillar ", 24 },
        { LAND, "Mt. Ember Exterior ", 25 },
        { LAND, "Mt. Ember Summit Path 1F ", 26 },
        { LAND, "Mt. Ember Summit Path 2F ", 27 },
        { LAND, "Mt. Ember Summit Path 3F ", 28 },
        { LAND, "Mt. Ember Ruby Path 1F ", 29 },
        { LAND, "Mt. Ember Ruby Path B1F", 30 },
        { LAND, "Mt. Ember Ruby Path B2F ", 31 },
        { LAND, "Mt. Ember Ruby Path B3F", 32 },
        { LAND, "Mt. Moon 1F", 33 },
        { LAND, "Mt. Moon B1F", 34 },
        { LAND, "Mt. Moon B2F", 35 },
        { LAND, "Pattern Bush", 36 },
        { LAND, "Pokémon Mansion Upper Floors", 37 },
        { LAND, "Pokémon Mansion Basement", 38 },
        { LAND, "Pokémon Tower 3F", 39 },
        { LAND, "Pokémon Tower 4F", 40 },
        { LAND, "Pokémon Tower 5F", 41 },
        { LAND, "Pokémon Tower 6F", 42 },
        { LAND, "Pokémon Tower 7F", 43 },
        { LAND, "Power Plant", 44 },
        { LAND, "Rock Tunnel 1F", 45 },
        { LAND, "Rock Tunnel B1F", 46 },
        { LAND, "Route 1", 47 },
        { LAND, "Route 2", 48 },
        { LAND, "Route 3", 49 },
        { LAND, "Route 4", 50 },
        { LAND, "Route 5", 51 },
        { LAND, "Route 6", 52 },
        { LAND, "Route 7", 53 },
        { LAND, "Route 8", 54 },
        { LAND, "Route 9", 55 },
        { LAND, "Route 10", 56 },
        { LAND, "Route 11", 57 },
        { LAND, "Route 12", 58 },
        { LAND, "Route 13", 59 },
        { LAND, "Route 14", 60 },
        { LAND, "Route 15", 61 },
        { LAND, "Route 16", 62 },
        { LAND, "Route 17", 63 },
        { LAND, "Route 18", 64 },
        { LAND, "Route 21", 65 },
        { LAND, "Route 22", 66 },
        { LAND, "Route 23", 67 },
        { LAND, "Route 24", 68 },
        { LAND, "Route 25", 69 },
        { LAND, "Ruin Valley", 70 },
        { LAND, "Safari Zone Entrance", 71 },
        { LAND, "Safari Zone Area 1 - East", 72 },
        { LAND, "Safari Zone Area 2 - North", 73 },
        { LAND, "Safari Zone Area 3 - West", 74 },
        { LAND, "Seafoam Islands 1F", 75 },
        { LAND, "Seafoam Islands B1F", 76 },
        { LAND, "Seafoam Islands B2F", 77 },
        { LAND, "Seafoam Islands B3F", 78 },
        { LAND, "Seafoam Islands B4F", 79 },
        { LAND, "Sevault Canyon Entrance", 80 },
        { LAND, "Sevault Canyon", 81 },
        { LAND, "Tanoby Ruins Chambers", 82 },
        { LAND, "Three Isle Port", 83 },
        { LAND, "Treasure Beach", 84 },
        { LAND, "Victory Road 1F", 85 },
        { LAND, "Victory Road 2F", 86 },
        { LAND, "Victory Road 3F", 87 },
        { LAND, "Viridian Forest", 88 },
        { LAND, "Water Path", 89 },
};

static const AreaEntry waterAreaMap[49] = {
        { WATER, "Berry Forest", 1 },
        { WATER, "Bond Bridge", 2 },
        { WATER, "Cape Brink", 3 },
        { WATER, "Celadon City", 4 },
        { WATER, "Cerulean Cave 1F", 5 },
        { WATER, "Cerulean Cave B1F", 6 },
        { WATER, "Cerulean City", 7 },
        { WATER, "Cinnabar Island", 8 },
        { WATER, "Five Island", 9 },
        { WATER, "Five Isle Meadow", 10 },
        { WATER, "Four Island", 11 },
        { WATER, "Fuchsia City", 12 },
        { WATER, "Green Path", 13 },
        { WATER, "Icefall Cave Entrance", 14 },
        { WATER, "Icefall Cave Back Cavern", 15 },
        { WATER, "Kindle Road", 16 },
        { WATER, "Memorial Pillar", 17 },
        { WATER, "One Island", 18 },
        { WATER, "Outcast Island", 19 },
        { WATER, "Pallet Town", 20 },
        { WATER, "Resort Gorgeous", 21 },
        { WATER, "Route 4", 22 },
        { WATER, "Route 6", 23 },
        { WATER, "Route 10", 24 },
        { WATER, "Route 11", 25 },
        { WATER, "Route 12", 26 },
        { WATER, "Route 13", 27 },
        { WATER, "Route 19", 28 },
        { WATER, "Route 20", 29 },
        { WATER, "Route 21", 30 },
        { WATER, "Route 22", 31 },
        { WATER, "Route 23", 32 },
        { WATER, "Route 24", 33 },
        { WATER, "Route 25", 34 },
        { WATER, "Ruin Valley", 35 },
        { WATER, "S.S. Anne", 36 },
        { WATER, "Safari Zone Entrance", 37 },
        { WATER, "Safari Zone Area 1 - East", 38 },
        { WATER, "Safari Zone Area 2 - North", 39 },
        { WATER, "Safari Zone Area 3 - West", 40 },
        { WATER, "Seafoam Islands B3F", 41 },
        { WATER, "Seafoam Islands B4F", 42 },
        { WATER, "Tanoby Ruins", 43 },
        { WATER, "Trainer Tower", 44 },
        { WATER, "Treasure Beach", 45 },
        { WATER, "Vermilion City", 46 },
        { WATER, "Viridian City", 47 },
        { WATER, "Water Labyrinth", 48 },
        { WATER, "Water Path", 49 }
};

static const AreaEntry rockAreaMap[12] = {
        { ROCKSMASH, "Cerulean Cave 1F", 1 },
        { ROCKSMASH, "Cerulean Cave 2F", 2 },
        { ROCKSMASH, "Cerulean Cave B1F", 3 },
        { ROCKSMASH, "Kindle Road", 4 },
        { ROCKSMASH, "Mt. Ember Exterior", 5 },
        { ROCKSMASH, "Mt. Ember Summit Path 2F", 6 },
        { ROCKSMASH, "Mt. Ember Ruby Path 1F", 7 },
        { ROCKSMASH, "Mt. Ember Ruby Path B1F", 8 },
        { ROCKSMASH, "Mt. Ember Ruby Path B2F", 9 },
        { ROCKSMASH, "Mt. Ember Ruby Path B3F", 10 },
        { ROCKSMASH, "Rock Tunnel B1F", 11 },
        { ROCKSMASH, "Sevault Canyon", 12 },
};

static const EncounterFileMap encMappings[] = {
        { FR, LAND,         "land"  },
        { FR, ROCKSMASH,    "rock"  },
        { FR, WATER,        "water" },
        { LG, LAND,         "land"  },
        { LG, ROCKSMASH,    "rock"  },
        { LG, WATER,        "water" },
};

const char *get_encounter_file_path(GameVersion gv, AreaType at);
Slot *load_slots(AreaEntry area, const char *fn);

#endif