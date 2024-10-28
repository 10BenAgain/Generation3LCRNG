#include "../include/filters.h"

void pushSEnc(senc_node** h, StaticEncounter enc) {
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

void pushWenc(wenc_node** h, WildEncounter enc) {
    wenc_node* temp = NULL;

    temp = (wenc_node*)malloc(sizeof(wenc_node));
    if (temp == NULL)
        return;

    temp->we = enc;
    temp->next = *h;

    *h = temp;
}

void print_sencounter_list(senc_node* enc) {
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

void print_wencounter_list(wenc_node* enc) {
    wenc_node* temp = NULL;
    temp = enc;

    int i, c;
    c = 0;
    while(temp != NULL) {
        Pokemon m = pokemon[temp->we.mon];
        printf("%d | ", c);
        printf("%s | ", m.name);
        printf("%d | ", temp->we.slot);
        printf("%d | ", temp->we.level);
        printf("%X | ", temp->we.PID);
        printf("%s | ", get_nature_str(temp->we.nature));
        printf("%s | ", (temp->we.ability) ? m.ab1 : m.ab0);

        for (i = 0; i < 6; i ++) {
            printf("%d | ", temp->we.IVs[i]);
        }

        printf("| %s ", shiny_types[temp->we.shiny]);
        printf("| %s ", temp->we.hp);
        printf("| %d \n", temp->we.hp_pow);

        temp = temp->next;
        c++;
    }
}

void freeSEncList(senc_node* head) {
    senc_node* currentTemp = head;
    senc_node *next = NULL;
    while(currentTemp != NULL) {
        next = currentTemp->next;
        free(currentTemp);
        currentTemp = next;
    }
}

void freeWEncList(wenc_node* head) {
    wenc_node* currentTemp = head;
    wenc_node *next = NULL;
    while(currentTemp != NULL) {
        next = currentTemp->next;
        free(currentTemp);
        currentTemp = next;
    }
}

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

void generateWildEncounter(
        wenc_node** list,
        Player pl,
        Method met,
        AreaEntry aEntry,
        GameVersion gv,
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
        increment_seed(&current_seed, 2);

        enc->nature = (current_seed >> 16) % 25;
        do
        {
            // PID re-roll https://docs.google.com/spreadsheets/d/1hCZznFa4cez3l2qx1DmYPbuB_dNGTqqCoaksZf-Q44s/edit?usp=sharing
            increment_seed(&current_seed, 1);
            uint32_t second_half = current_seed >> 16;
            increment_seed(&current_seed, 1);
            uint32_t first_half = current_seed >> 16;
            enc->PID = (first_half << 16) | second_half;
        } while (enc->PID % 25 != enc->nature);

        enc->ability = enc->PID & 1;

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

        enc->shiny = is_shiny(enc->PID, pl.TID, pl.SID);
        enc->hp = HP[get_hp_value(enc->IVs)].type;
        enc->hp_pow = get_hp_power(enc->IVs);

        pushWenc(list, *enc);
    }
}
