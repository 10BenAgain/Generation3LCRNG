#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "../external/inih/ini.h"

/* https://github.com/benhoyt/inih?tab=readme-ov-file#simple-example-in-c */
typedef struct {
    const char* name;
    uint32_t sid;
    uint32_t tid;
    const char* game_version;
    const char* language;
    uint8_t sub_version;
    const char* audio;
    const char* seed;
    const char* button;
} Config;

typedef struct {
    GameVersion gv;
    JPNVersion jgv;
    Language lang;
    AudioSetting audio;
    ButtonSetting buttonSetting;
    ButtonSeed buttonSeed;
} Settings;

int handler(void* player, const char* section, const char* name, const char * value);

void loadSettings(Config* cf, Settings *set);

#endif
