#include "pokemon.h"
#include <stdlib.h>


const char* gender_s[] = {
    "Male",
    "Female",
    "None"
};

const char* shiny_types[] = {
        "None",
        "Star",
        "Square"
};

const char* encounter_category[] = {
        "Starter",
        "Fossil",
        "Gift",
        "Game Corner",
        "Stationary",
        "Legends",
        "Events",
        "Roamers"
};

const HiddenPower HP[16] = {
    {0,     "Fighting"  },
    {1,     "Flying"    },
    {2,     "Poison"    },
    {3,     "Ground"    },
    {4,     "Rock"      },
    {5,     "Bug"       },
    {6,     "Ghost"     },
    {7,     "Steel"     },
    {8,     "Fire"      },
    {9,     "Water"     },
    {10,    "Grass"     },
    {11,    "Electric"  },
    {12,    "Psychic"   },
    {13,    "Ice"       },
    {14,    "Dragon"    },
    {15,    "Dark"      }
};

const Nature natures[25] = {
        {0,     "Hardy"     },
        {1,     "Lonely"    },
        {2,     "Brave"     },
        {3,     "Adamant"   },
        {4,     "Naughty"   },
        {5,     "Bold"      },
        {6,     "Docile"    },
        {7,     "Relaxed"   },
        {8,     "Impish"    },
        {9,     "Lax"       },
        {10,    "Timid"     },
        {11,    "Hasty"     },
        {12,    "Serious"   },
        {13,    "Jolly"     },
        {14,    "Naive"     },
        {15,    "Modest"    },
        {16,    "Mild"      },
        {17,    "Quiet"     },
        {18,    "Bashful"   },
        {19,    "Rash"      },
        {20,    "Calm"      },
        {21,    "Gentle"    },
        {22,    "Sassy"     },
        {23,    "Careful"   },
        {24,    "Quirky"    }
};
/* ATK/DEF/SPA/SPD/SPE */
const NatureMult nature_mult_table[25] = {
    { 0,   {1.0,   1.0,   1.0,   1.0,   1.0}  },
    { 1,   {1.1,   0.9,   1.0,   1.0,   1.0}  },
    { 2,   {1.1,   1.0,   1.0,   1.0,   0.9}  },
    { 3,   {1.1,   1.0,   0.9,   1.0,   1.0}  },
    { 4,   {1.1,   1.0,   1.0,   0.9,   1.0}  },
    { 5,   {0.9,   1.1,   1.0,   1.0,   1.0}  },
    { 6,   {1.0,   1.0,   1.0,   1.0,   1.0}  },
    { 7,   {1.0,   1.1,   1.0,   1.0,   0.9}  },
    { 8,   {1.0,   1.1,   0.9,   1.0,   1.0}  },
    { 9,   {1.0,   1.1,   1.0,   0.9,   1.0}  },
    {10,   {0.9,   1.0,   1.0,   1.0,   1.1}  },
    {11,   {1.0,   0.9,   1.0,   1.0,   1.1}  },
    {12,   {1.0,   1.0,   1.0,   1.0,   1.0}  },
    {13,   {1.0,   1.0,   0.9,   1.0,   1.1}  },
    {14,   {1.0,   1.0,   1.0,   0.9,   1.1}  },
    {15,   {0.9,   1.0,   1.1,   1.0,   1.0}  },
    {16,   {1.0,   0.9,   1.1,   1.0,   1.0}  },
    {17,   {1.0,   1.0,   1.1,   1.0,   0.9}  },
    {18,   {1.0,   1.0,   1.0,   1.0,   1.0}  },
    {19,   {1.0,   1.0,   1.1,   0.9,   1.0}  },
    {20,   {0.9,   1.0,   1.0,   1.1,   1.0}  },
    {21,   {1.0,   0.9,   1.0,   1.1,   1.0}  },
    {22,   {1.0,   1.0,   1.0,   1.1,   0.9}  },
    {23,   {1.0,   1.0,   0.9,   1.1,   1.0}  },
    {24,   {1.0,   1.0,   1.0,   1.0,   1.0}  },

};

const Pokemon pokemon[151] = {
        { 1, "Bulbasaur", {45, 49, 49, 65, 65, 45}, F1M7 },
        { 2, "Ivysaur", {60, 62, 63, 80, 80, 60}, F1M7 },
        { 3, "Venusaur", {80, 82, 83, 100, 100, 80}, F1M7 },
        { 4, "Charmander", {39, 52, 43, 60, 50, 65}, F1M7 },
        { 5, "Charmeleon", {58, 64, 58, 80, 65, 80}, F1M7 },
        { 6, "Charizard", {78, 84, 78, 109, 85, 100}, F1M7 },
        { 7, "Squirtle", {44, 48, 65, 50, 64, 43}, F1M7 },
        { 8, "Wartortle", {59, 63, 80, 65, 80, 58}, F1M7 },
        { 9, "Blastoise", {79, 83, 100, 85, 105, 78}, F1M7 },
        { 10, "Caterpie", {45, 30, 35, 20, 20, 45}, F1M1 },
        { 11, "Metapod", {50, 20, 55, 25, 25, 30}, F1M1 },
        { 12, "Butterfree", {60, 45, 50, 90, 80, 70}, F1M1 },
        { 13, "Weedle", {40, 35, 30, 20, 20, 50}, F1M1 },
        { 14, "Kakuna", {45, 25, 50, 25, 25, 35}, F1M1 },
        { 15, "Beedrill", {65, 90, 40, 45, 80, 75}, F1M1 },
        { 16, "Pidgey", {40, 45, 40, 35, 35, 56}, F1M1 },
        { 17, "Pidgeotto", {63, 60, 55, 50, 50, 71}, F1M1 },
        { 18, "Pidgeot", {83, 80, 75, 70, 70, 101}, F1M1 },
        { 19, "Rattata", {30, 56, 35, 25, 35, 72}, F1M1 },
        { 20, "Raticate", {55, 81, 60, 50, 70, 97}, F1M1 },
        { 21, "Spearow", {40, 60, 30, 31, 31, 70}, F1M1 },
        { 22, "Fearow", {65, 90, 65, 61, 61, 100}, F1M1 },
        { 23, "Ekans", {35, 60, 44, 40, 54, 55}, F1M1 },
        { 24, "Arbok", {60, 95, 69, 65, 79, 80}, F1M1 },
        { 25, "Pikachu", {35, 55, 40, 50, 50, 90}, F1M1 },
        { 26, "Raichu", {60, 90, 55, 90, 80, 110}, F1M1 },
        { 27, "Sandshrew", {50, 75, 85, 20, 30, 40}, F1M1 },
        { 28, "Sandslash", {75, 100, 110, 45, 55, 65}, F1M1 },
        { 29, "Nidoran-f", {55, 47, 52, 40, 40, 41}, FemaleOnly },
        { 30, "Nidorina", {70, 62, 67, 55, 55, 56}, FemaleOnly },
        { 31, "Nidoqueen", {90, 92, 87, 75, 85, 76}, FemaleOnly },
        { 32, "Nidoran-m", {46, 57, 40, 40, 40, 50}, MaleOnly },
        { 33, "Nidorino", {61, 72, 57, 55, 55, 65}, MaleOnly },
        { 34, "Nidoking", {81, 102, 77, 85, 75, 85}, MaleOnly },
        { 35, "Clefairy", {70, 45, 48, 60, 65, 35}, F3M1 },
        { 36, "Clefable", {95, 70, 73, 95, 90, 60}, F3M1 },
        { 37, "Vulpix", {38, 41, 40, 50, 65, 65}, F3M1 },
        { 38, "Ninetales", {73, 76, 75, 81, 100, 100}, F3M1 },
        { 39, "Jigglypuff", {115, 45, 20, 45, 25, 20}, F3M1 },
        { 40, "Wigglytuff", {140, 70, 45, 85, 50, 45}, F3M1 },
        { 41, "Zubat", {40, 45, 35, 30, 40, 55}, F1M1 },
        { 42, "Golbat", {75, 80, 70, 65, 75, 90}, F1M1 },
        { 43, "Oddish", {45, 50, 55, 75, 65, 30}, F1M1 },
        { 44, "Gloom", {60, 65, 70, 85, 75, 40}, F1M1 },
        { 45, "Vileplume", {75, 80, 85, 110, 90, 50}, F1M1 },
        { 46, "Paras", {35, 70, 55, 45, 55, 25}, F1M1 },
        { 47, "Parasect", {60, 95, 80, 60, 80, 30}, F1M1 },
        { 48, "Venonat", {60, 55, 50, 40, 55, 45}, F1M1 },
        { 49, "Venomoth", {70, 65, 60, 90, 75, 90}, F1M1 },
        { 50, "Diglett", {10, 55, 25, 35, 45, 95}, F1M1 },
        { 51, "Dugtrio", {35, 100, 50, 50, 70, 120}, F1M1 },
        { 52, "Meowth", {40, 45, 35, 40, 40, 90}, F1M1 },
        { 53, "Persian", {65, 70, 60, 65, 65, 115}, F1M1 },
        { 54, "Psyduck", {50, 52, 48, 65, 50, 55}, F1M1 },
        { 55, "Golduck", {80, 82, 78, 95, 80, 85}, F1M1 },
        { 56, "Mankey", {40, 80, 35, 35, 45, 70}, F1M1 },
        { 57, "Primeape", {65, 105, 60, 60, 70, 95}, F1M1 },
        { 58, "Growlithe", {55, 70, 45, 70, 50, 60}, F1M3 },
        { 59, "Arcanine", {90, 110, 80, 100, 80, 95}, F1M3 },
        { 60, "Poliwag", {40, 50, 40, 40, 40, 90}, F1M1 },
        { 61, "Poliwhirl", {65, 65, 65, 50, 50, 90}, F1M1 },
        { 62, "Poliwrath", {90, 95, 95, 70, 90, 70}, F1M1 },
        { 63, "Abra", {25, 20, 15, 105, 55, 90}, F1M3 },
        { 64, "Kadabra", {40, 35, 30, 120, 70, 105}, F1M3 },
        { 65, "Alakazam", {55, 50, 45, 135, 95, 120}, F1M3 },
        { 66, "Machop", {70, 80, 50, 35, 35, 35}, F1M3 },
        { 67, "Machoke", {80, 100, 70, 50, 60, 45}, F1M3 },
        { 68, "Machamp", {90, 130, 80, 65, 85, 55}, F1M3 },
        { 69, "Bellsprout", {50, 75, 35, 70, 30, 40}, F1M1 },
        { 70, "Weepinbell", {65, 90, 50, 85, 45, 55}, F1M1 },
        { 71, "Victreebel", {80, 105, 65, 100, 70, 70}, F1M1 },
        { 72, "Tentacool", {40, 40, 35, 50, 100, 70}, F1M1 },
        { 73, "Tentacruel", {80, 70, 65, 80, 120, 100}, F1M1 },
        { 74, "Geodude", {40, 80, 100, 30, 30, 20}, F1M1 },
        { 75, "Graveler", {55, 95, 115, 45, 45, 35}, F1M1 },
        { 76, "Golem", {80, 120, 130, 55, 65, 45}, F1M1 },
        { 77, "Ponyta", {50, 85, 55, 65, 65, 90}, F1M1 },
        { 78, "Rapidash", {65, 100, 70, 80, 80, 105}, F1M1 },
        { 79, "Slowpoke", {90, 65, 65, 40, 40, 15}, F1M1 },
        { 80, "Slowbro", {95, 75, 110, 100, 80, 30}, F1M1 },
        { 81, "Magnemite", {25, 35, 70, 95, 55, 45}, Unknown },
        { 82, "Magneton", {50, 60, 95, 120, 70, 70}, Unknown },
        { 83, "Farfetch'd", {52, 90, 55, 58, 62, 60}, F1M1 },
        { 84, "Doduo", {35, 85, 45, 35, 35, 75}, F1M1 },
        { 85, "Dodrio", {60, 110, 70, 60, 60, 110}, F1M1 },
        { 86, "Seel", {65, 45, 55, 45, 70, 45}, F1M1 },
        { 87, "Dewgong", {90, 70, 80, 70, 95, 70}, F1M1 },
        { 88, "Grimer", {80, 80, 50, 40, 50, 25}, F1M1 },
        { 89, "Muk", {105, 105, 75, 65, 100, 50}, F1M1 },
        { 90, "Shellder", {30, 65, 100, 45, 25, 40}, F1M1 },
        { 91, "Cloyster", {50, 95, 180, 85, 45, 70}, F1M1 },
        { 92, "Gastly", {30, 35, 30, 100, 35, 80}, F1M1 },
        { 93, "Haunter", {45, 50, 45, 115, 55, 95}, F1M1 },
        { 94, "Gengar", {60, 65, 60, 130, 75, 110}, F1M1 },
        { 95, "Onix", {35, 45, 160, 30, 45, 70}, F1M1 },
        { 96, "Drowzee", {60, 48, 45, 43, 90, 42}, F1M1 },
        { 97, "Hypno", {85, 73, 70, 73, 115, 67}, F1M1 },
        { 98, "Krabby", {30, 105, 90, 25, 25, 50}, F1M1 },
        { 99, "Kingler", {55, 130, 115, 50, 50, 75}, F1M1 },
        { 100, "Voltorb", {40, 30, 50, 55, 55, 100}, Unknown },
        { 101, "Electrode", {60, 50, 70, 80, 80, 150}, Unknown },
        { 102, "Exeggcute", {60, 40, 80, 60, 45, 40}, F1M1 },
        { 103, "Exeggutor", {95, 95, 85, 125, 75, 55}, F1M1 },
        { 104, "Cubone", {50, 50, 95, 40, 50, 35}, F1M1 },
        { 105, "Marowak", {60, 80, 110, 50, 80, 45}, F1M1 },
        { 106, "Hitmonlee", {50, 120, 53, 35, 110, 87}, MaleOnly },
        { 107, "Hitmonchan", {50, 105, 79, 35, 110, 76}, MaleOnly },
        { 108, "Lickitung", {90, 55, 75, 60, 75, 30}, F1M1 },
        { 109, "Koffing", {40, 65, 95, 60, 45, 35}, F1M1 },
        { 110, "Weezing", {65, 90, 120, 85, 70, 60}, F1M1 },
        { 111, "Rhyhorn", {80, 85, 95, 30, 30, 25}, F1M1 },
        { 112, "Rhydon", {105, 130, 120, 45, 45, 40}, F1M1 },
        { 113, "Chansey", {250, 5, 5, 35, 105, 50}, FemaleOnly },
        { 114, "Tangela", {65, 55, 115, 100, 40, 60}, F1M1 },
        { 115, "Kangaskhan", {105, 95, 80, 40, 80, 90}, FemaleOnly },
        { 116, "Horsea", {30, 40, 70, 70, 25, 60}, F1M1 },
        { 117, "Seadra", {55, 65, 95, 95, 45, 85}, F1M1 },
        { 118, "Goldeen", {45, 67, 60, 35, 50, 63}, F1M1 },
        { 119, "Seaking", {80, 92, 65, 65, 80, 68}, F1M1 },
        { 120, "Staryu", {30, 45, 55, 70, 55, 85}, Unknown },
        { 121, "Starmie", {60, 75, 85, 100, 85, 115}, Unknown },
        { 122, "Mr-mime", {40, 45, 65, 100, 120, 90}, F1M1 },
        { 123, "Scyther", {70, 110, 80, 55, 80, 105}, F1M1 },
        { 124, "Jynx", {65, 50, 35, 115, 95, 95}, FemaleOnly },
        { 125, "Electabuzz", {65, 83, 57, 95, 85, 105}, F1M3 },
        { 126, "Magmar", {65, 95, 57, 100, 85, 93}, F1M3 },
        { 127, "Pinsir", {65, 125, 100, 55, 70, 85}, F1M1 },
        { 128, "Tauros", {75, 100, 95, 40, 70, 110}, MaleOnly },
        { 129, "Magikarp", {20, 10, 55, 15, 20, 80}, F1M1 },
        { 130, "Gyarados", {95, 125, 79, 60, 100, 81}, F1M1 },
        { 131, "Lapras", {130, 85, 80, 85, 95, 60}, F1M1 },
        { 132, "Ditto", {48, 48, 48, 48, 48, 48}, Unknown },
        { 133, "Eevee", {55, 55, 50, 45, 65, 55}, F1M7 },
        { 134, "Vaporeon", {130, 65, 60, 110, 95, 65}, F1M7 },
        { 135, "Jolteon", {65, 65, 60, 110, 95, 130}, F1M7 },
        { 136, "Flareon", {65, 130, 60, 95, 110, 65}, F1M7 },
        { 137, "Porygon", {65, 60, 70, 85, 75, 40}, Unknown },
        { 138, "Omanyte", {35, 40, 100, 90, 55, 35}, F1M7 },
        { 139, "Omastar", {70, 60, 125, 115, 70, 55}, F1M7 },
        { 140, "Kabuto", {30, 80, 90, 55, 45, 55}, F1M7 },
        { 141, "Kabutops", {60, 115, 105, 65, 70, 80}, F1M7 },
        { 142, "Aerodactyl", {80, 105, 65, 60, 75, 130}, F1M7 },
        { 143, "Snorlax", {160, 110, 65, 65, 110, 30}, F1M7 },
        { 144, "Articuno", {90, 85, 100, 95, 125, 85}, Unknown },
        { 145, "Zapdos", {90, 90, 85, 125, 90, 100}, Unknown },
        { 146, "Moltres", {90, 100, 90, 125, 85, 90}, Unknown },
        { 147, "Dratini", {41, 64, 45, 50, 50, 50}, F1M1 },
        { 148, "Dragonair", {61, 84, 65, 70, 70, 70}, F1M1 },
        { 149, "Dragonite", {91, 134, 95, 100, 100, 80}, F1M1 },
        { 150, "Mewtwo", {106, 110, 90, 154, 90, 130}, Unknown },
        { 151, "Mew", {100, 100, 100, 100, 100, 100}, Unknown }
};

const Encounter StaticEncounters[] = {
        {Starters,      "Bulbasaur",    5},
        {Starters,      "Charmander",   5},
        {Starters,      "Squirtle",     5},
        {Fossils,       "Omanyte",      5},
        {Fossils,       "Kabuto",       5},
        {Fossils,       "Aerodactyl",   5},
        {Gifts,         "Hitmonlee",    25},
        {Gifts,         "Hitmonchan",   25},
        {Gifts,         "Magikarp",     5},
        {Gifts,         "Lapras",       25},
        {Gifts,         "Eevee",        25},
        {Gifts,         "Togepi",       5},
        {GameCorner,    "Abra",         9},
        {GameCorner,    "Clefairy",     8},
        {GameCorner,    "Scyther",      25},
        {GameCorner,    "Pinsir",       25},
        {GameCorner,    "Dratini",      18},
        {GameCorner,    "Porygon",      26},
        {Stationary,    "Snorlax",      30},
        {Stationary,    "Hypno",        30},
        {Stationary,    "Electrode",    34},
        {Legends,       "Articuno",     50},
        {Legends,       "Zapdos",       50},
        {Legends,       "Moltres",      50},
        {Legends,       "Mewtwo",       70},
        {Events,        "Deoxys",       30},
        {Events,        "Lugia",        70},
        {Events,        "Ho-Oh",        70},
        {Roamers,       "Raikou",       50},
        {Roamers,       "Entei",        50},
        {Roamers,       "Suicune",      50},
};

const char*
get_nature_str(uint8_t key) {
    if (key > sizeof(natures)/sizeof(natures[0]))
        return "Huh?!";
    return natures[key].name;
}

const char*
get_gender_str(uint8_t key) {
    switch (key)
    {
    case 0:
    case 1:
        return gender_s[key];
    default:
        return gender_s[2];
    }
}

uint8_t
is_shiny(uint32_t PID, uint32_t TID, uint32_t SID) {
    uint16_t psv = (TID ^ SID) ^ (PID >> 16) ^ (PID & 0xFFFF);

    if (psv == 0)
        return 2;
    else if (psv < 8)
        return 1;
    else
        return 0;
}

uint8_t
get_gender(uint32_t PID, GenderRatio gr) {
    switch (gr)
        {
        case 0:
        case 1:
        case 3:
            return gr;
        default:
            return (PID & 255) < gr;
        }
};

// https://bulbapedia.bulbagarden.net/wiki/Hidden_Power_(move)/Calculation
uint8_t
get_hp_value(uint8_t *IVs) {
    int sum = 0;
    int i, j;
    for (i = 0, j = 1; i < 3; i++, j *= 2) {
        sum += (IVs[i] % 2) * j;
    }
    sum += (IVs[5] % 2) * 8;
    sum += (IVs[3] % 2) * 16;
    sum += (IVs[4] % 2) * 32;

    return (sum * 15) / 63;
}

uint8_t
get_hp_power(uint8_t *IVs) {
    int sum = 0;
    int i, j;
    for (i = 0, j = 1; i < 3; i++, j *= 2) {
        sum += ((IVs[i] >> 1) & 1) * j;
    }
    sum += ((IVs[5] >> 1) & 1) * 8;
    sum += ((IVs[3] >> 1) & 1) * 16;
    sum += ((IVs[4] >> 1) & 1) * 32;

    return (int)((sum * 40) / 63) + 30;
}

// https://bulbapedia.bulbagarden.net/wiki/Personality_value#Unown.27s_letter
// 0000011 00000011 00000011 00000011 = (0x3030303 & 3000000) = (00000011 00000000 00000000 00000000) >> 18 = 1100 0000
// 0000011 00000011 00000011 00000011 = (0x3030303 & 30000  ) = (         00000011 00000000 00000000) >> 12 = 0011 0000
// 0000011 00000011 00000011 00000011 = (0x3030303 & 300  ) =   (                  00000011 00000000) >> 6  = 0000 1100
// 0000011 00000011 00000011 00000011 = (0x3030303 & 3  ) =   (                             00000011)

uint8_t
get_unown_shape(uint32_t PID) {
    return (
        ((PID & 0x3000000) >> 18) |
        ((PID & 0x30000) >> 12) |
        ((PID & 0x300) >> 6) |
        (PID & 0x3)) % 28;
}

char
unown_symbols(int val) {
    if (val > 25) {
        switch (val) {
            case 26:
                return '!';
            case 27:
                return '?';
            default:
                return '$';
        }
    } else
        return (char)(val + 65);
}

uint8_t* get_iv_range(int level, Nature nature, int base_stat, int stat_total, int stat_num, int ev) {

    uint8_t* ivs = malloc(sizeof(uint8_t) * 2);
    int lower_bound, upper_bound, temp_stat_total, i;
    if (level < 1 || level > 100 || base_stat < 1 || stat_total < 1 || ev < 0 || ev > 255) {
        return NULL;
    }
    if (ev > 252){
        ev = 252;
    }

    if (stat_num == 0) {
        lower_bound = ((stat_total - 10.0) * 100.0) / level - 2*base_stat - ev /4.0 - 100.0;
        upper_bound = lower_bound;
        temp_stat_total = ((2.0*base_stat + upper_bound + 1 + ev/4.0 + 100.0) * level) / 100.0 + 10.0;
        for (i = lower_bound; temp_stat_total == stat_total; i++){
            upper_bound++;
            temp_stat_total = ((2.0*base_stat + upper_bound+ 1 + ev/4.0 + 100.0) * level) / 100.0 + 10.0;
        }

    } else {
        float nature_mult = nature_mult_table[nature.key].mults[stat_num - 1];
        lower_bound = ((stat_total/nature_mult - 5.0) * 100.0) / level - 2.0*base_stat - ev/4.0;
        upper_bound = lower_bound;
        temp_stat_total = stat_total = (((2.0*base_stat + upper_bound + 1 + ev/4.0) * level) / 100.0 + 5.0) * nature_mult;
        for (i = lower_bound; temp_stat_total == stat_total; i++){
            upper_bound++;
            temp_stat_total = (((2.0*base_stat + upper_bound + 1 + ev/4.0) * level) / 100.0 + 5.0) * nature_mult;
        }
    }
    ivs[0] = lower_bound;
    ivs[1] = upper_bound;

    return ivs;

}
