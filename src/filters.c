#include "../include/filters.h"

void pushSEnc(senc_node** h, StaticEncounter enc);
void pushWenc(wenc_node** h, WildEncounter enc);

uint8_t ivFilterCheckWild(WildEncounter* we, WildFilter* filter);
uint8_t abilityFilterCheckWild(WildFilter* filter, uint8_t ability);
uint8_t genderFilterCheckWild(WildFilter* filter, uint8_t gender);
uint8_t natureFilterCheckWild(WildFilter* filter, uint8_t nature);
uint8_t shinyFilterCheckWild(WildFilter* filter, uint8_t shiny);

void generate_m1_static(senc_node** list, Player pl, uint16_t mon, uint32_t seed, uint32_t init, uint32_t max) {
    if (max <= 0) {
        return;
    }

    uint32_t advances;
    advances = max - init;
    if (advances <= 0) {
        return;
    }

    seed = jump_ahead(Gen3JumpTable, seed, init);

    int i;
    for (i = 0; i <= (int)advances; i++, increment_seed(&seed, 1)) {
        uint32_t current_seed = seed;

        StaticEncounter* enc = NULL;
        enc = (StaticEncounter*) malloc(sizeof(StaticEncounter));

        if (enc == NULL) {
            printf("Memory allocation failed");
            return;
        }

        enc->mon = mon;
        increment_seed(&current_seed, 1);

        uint32_t second_half = current_seed >> 16;
        increment_seed(&current_seed, 1);
        uint32_t first_half = current_seed >> 16;

        enc->PID = (first_half << 16) | second_half;

        increment_seed(&current_seed, 1);

        enc->IVs[0] = (current_seed >> 16) & IV_MASK; // HP
        enc->IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
        enc->IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

        // Move RNG by one
        increment_seed(&current_seed, 1);
        enc->IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
        enc->IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
        enc->IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe

        enc->nature = enc->PID % 25;
        enc->ability = enc->PID & 1;

        enc->shiny = is_shiny(enc->PID, pl.TID, pl.SID);
        enc->gender = get_gender_str(get_gender(enc->PID, pokemon[mon].gr));
        enc->hp = HP[get_hp_value(enc->IVs)].type;
        enc->hp_pow = get_hp_power(enc->IVs);

        pushSEnc(list, *enc);
    }
}

void generateWildEncountersFromSeedList(
        wenc_node** list,
        Player pl,
        Method met,
        AreaEntry aEntry,
        GameVersion gv,
        WildFilter filter,
        InitialSeed *seeds,
        uint32_t size,
        uint32_t init,
        uint32_t max) {

    for (size_t i = 0; i < size; i ++) {
        generateWildEncounter(list, pl, met, aEntry, gv, filter, seeds[i].seed, init, max);
    }
};

void generateWildEncounter(
        wenc_node** list,
        Player pl,
        Method met,
        AreaEntry aEntry,
        GameVersion gv,
        WildFilter filter,
        uint32_t seed,
        uint32_t init,
        uint32_t max) {

    if (max <= 0) {
        return;
    }

    uint32_t advances;
    advances = max - init;
    if (advances <= 0) {
        return;
    }
    uint32_t initial_seed = seed;

    const char *encounter_data_path = get_encounter_file_path(gv, aEntry.at);
    Slot *slots = load_slots(aEntry, encounter_data_path);
    if (slots == NULL) {
        free(slots);
        return;
    }

    EncounterType et = area2enc(aEntry.at);
    seed = jump_ahead(Gen3JumpTable, seed, init);

    int i;
    for (i = 0; i <= (int)advances; i++, increment_seed(&seed, 1)) {
        uint32_t current_seed = seed;

        WildEncounter* enc = NULL;
        enc = (WildEncounter* )malloc(sizeof(WildEncounter));
        if (enc == NULL) {
            return;
        }

        enc->slot = get_enc_table(et)[nextUShort(100, current_seed)];
        increment_seed(&current_seed, 1);
        enc->level = calculate_level(slots[enc->slot], current_seed);
        enc->mon = slots[enc->slot].mon;

        if (!(enc->mon == filter.mon)){
            free(enc);
            continue;
        }

        increment_seed(&current_seed, 2);

        enc->nature = (current_seed >> 16) % 25;

        if (!natureFilterCheckWild(&filter, enc->nature)) {
            free(enc);
            continue;
        }

        do
        {
            // PID re-roll https://docs.google.com/spreadsheets/d/1hCZznFa4cez3l2qx1DmYPbuB_dNGTqqCoaksZf-Q44s/edit?usp=sharing
            increment_seed(&current_seed, 1);
            uint32_t second_half = current_seed >> 16;
            increment_seed(&current_seed, 1);
            uint32_t first_half = current_seed >> 16;
            enc->PID = (first_half << 16) | second_half;
        } while (enc->PID % 25 != enc->nature);

        enc->shiny = is_shiny(enc->PID, pl.TID, pl.SID);

        if (!shinyFilterCheckWild(&filter, enc->shiny)) {
            free(enc);
            continue;
        }

        Pokemon poke = pokemon[enc->mon];

        if (!genderFilterCheckWild(&filter, get_gender(enc->PID, poke.gr))) {
            free(enc);
            continue;
        }

        enc->ability = enc->PID & 1;

        if (!abilityFilterCheckWild(&filter, enc->ability)) {
            free(enc);
            continue;
        }

        if (met == H2) {
            increment_seed(&current_seed, 1);
        }

        increment_seed(&current_seed, 1);

        enc->IVs[0] = (current_seed >> 16) & IV_MASK; // HP
        enc->IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
        enc->IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

        if (met == H4) {
            increment_seed(&current_seed, 1);
        }
        // Move RNG by one
        increment_seed(&current_seed, 1);
        enc->IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
        enc->IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
        enc->IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe

        if (!ivFilterCheckWild(enc, &filter)) {
            free(enc);
            continue;
        }

        enc->hp = HP[get_hp_value(enc->IVs)].type;
        enc->hp_pow = get_hp_power(enc->IVs);
        enc->advances = i;
        enc->seed = initial_seed;

        pushWenc(list, *enc);
    }
}


uint8_t
ivFilterCheckWild(WildEncounter* we, WildFilter* filter) {
    return (we->IVs[0] >= filter->hp_iv_bounds[0] && we->IVs[0] <= filter->hp_iv_bounds[1] &&
        we->IVs[1] >= filter->atk_iv_bounds[0] && we->IVs[1] <= filter->atk_iv_bounds[1] &&
        we->IVs[2] >= filter->def_iv_bounds[0] && we->IVs[0] <= filter->def_iv_bounds[1] &&
        we->IVs[3] >= filter->spa_iv_bounds[0] && we->IVs[1] <= filter->spa_iv_bounds[1] &&
        we->IVs[4] >= filter->spd_iv_bounds[0] && we->IVs[0] <= filter->spd_iv_bounds[1] &&
        we->IVs[5] >= filter->spe_iv_bounds[0] && we->IVs[1] <= filter->spe_iv_bounds[1] );
}

/* If filter ability == 2 then filter doesn't care about which ability otherwise check which ability is requested*/
uint8_t
abilityFilterCheckWild( WildFilter* filter, uint8_t ability) {
    if (filter->ability == 2)
        return 1;

    if (ability == filter->ability)
        return 1;
    else
        return 0;
}

uint8_t
genderFilterCheckWild(WildFilter* filter, uint8_t gender) {
    return  (filter->gender[0] == 1 && gender == 0) ||  // Male gender[0] == 1
            (filter->gender[1] == 1 && gender == 1) ||  // Female gender[1] == 1
            (filter->gender[2] == 1 && gender == 3);    // Genderless gender[2] == 1
}

uint8_t
shinyFilterCheckWild(WildFilter* filter, uint8_t shiny) {
    return (filter->shiny[0] == 1 && shiny == 2) ||     // Square shiny[0] == 1
           (filter->shiny[1] == 1 && shiny == 1) ||     // Star shiny[1] == 1
           (filter->shiny[2] == 1 && shiny == 0);       // None
}

uint8_t
natureFilterCheckWild(WildFilter* filter, uint8_t nature) {
    return (filter->natures[nature] == 1);
}

void
pushSEnc(senc_node** h, StaticEncounter enc) {
    // Create node pointer
    senc_node * temp = NULL;

    // Allocate memory to the pointer
    temp = (senc_node*)malloc(sizeof(senc_node));

    if (temp == NULL)
        return;

    // Set the value of its static encounter to the value passed by the function
    temp->se = enc;
    temp->next = *h;

    // Address of head is now the inserted temp pointer
    *h = temp;
}

void
pushWenc(wenc_node** h, WildEncounter enc) {
    wenc_node* temp = NULL;

    temp = (wenc_node*)malloc(sizeof(wenc_node));
    if (temp == NULL)
        return;

    temp->we = enc;
    temp->next = *h;

    *h = temp;
}

void
print_sencounter_list(senc_node* enc) {
    senc_node* temp = NULL;
    temp = enc;

    int i;
    while(temp != NULL) {
        printf("%X | ", temp->se.PID);
        printf("%s | ", get_nature_str(temp->se.nature));
        printf("Ability: %X | ", temp->se.ability );
        for (i = 0; i < 6; i ++) {
            printf("%d | ", temp->se.IVs[i]);
        }
        printf("| %s ", shiny_types[temp->se.shiny]);
        printf("| %s ", temp->se.hp);
        printf("| %d ", temp->se.hp_pow);
        printf("| %s \n", temp->se.gender);

        temp = temp->next;
    }
}

void
print_wencounter_list(wenc_node* enc) {
    wenc_node* temp = NULL;
    temp = enc;

    int i, c;
    c = 0;
    while(temp != NULL) {
        Pokemon m = pokemon[temp->we.mon];
        printf("%X | ", temp->we.seed);
        printf("%d | ", temp->we.advances);
        printf("%s | ", m.name);
        printf("%d | ", temp->we.slot);
        printf("%d | ", temp->we.level);
        printf("%X | ", temp->we.PID);
        printf("%s | ", get_nature_str(temp->we.nature));
        printf("%s | ", (temp->we.ability) ? m.ab1 : m.ab0);

        for (i = 0; i < 6; i ++) {
            printf("%d | ", temp->we.IVs[i]);
        }

        printf(" %s ", shiny_types[temp->we.shiny]);
        printf("| %s ", temp->we.hp);
        printf("| %d ", temp->we.hp_pow);
        printf("| %s\n", get_gender_str(get_gender(temp->we.PID, m.gr)));

        temp = temp->next;
        c++;
    }
}

void
freeSEncList(senc_node* head) {
    senc_node* currentTemp = head;
    senc_node *next = NULL;
    while(currentTemp != NULL) {
        next = currentTemp->next;
        free(currentTemp);
        currentTemp = next;
    }
}

void
freeWEncList(wenc_node* head) {
    wenc_node* currentTemp = head;
    wenc_node *next = NULL;
    while(currentTemp != NULL) {
        next = currentTemp->next;
        free(currentTemp);
        currentTemp = next;
    }
}