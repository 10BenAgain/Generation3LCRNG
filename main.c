#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "include/pokemon.h"
#include "include/generator.h"
#include "include/ivs.h"
#include "include/seeds.h"
#include "include/rng.h"
#include "include/filters.h"

int main() {
    /* Settings for target search */
    Player player;
    player.SID = 34437;
    player.TID = 44782;
    GameVersion gv = LG;
    Pokemon mon = pokemon[20]; // Spearow
    Nature nat = natures[8]; // Impish
    uint8_t level = 13;
    uint32_t target_seed = 0xE585;

    /* Declare the encounter type and the area where the encounter happens */
    EncounterType encT = Grass;
    AreaEntry at = landAreaMap[55]; // Route 10

    /*
     * Create a path to the seed data based on the game version and in game settings
     * gv = FR/LG
     * MONO = audio setting
     * LA = button setting
     * Start = seed button
    */
    const char* fp = get_seed_file_path(gv, MONO, LA, START);
    if (access(fp, F_OK)) {
        printf("Data files missing or not loaded properly!\n");
        return 1;
    }

    /* Declare variable to store the amount of seeds that are going to be added to the seeds array*/
    uint64_t len, s_len, index;

    /* Load the seed data based on the file path determined earlier */
    InitialSeed *seeds = load_initial_seeds(fp, &len);

    if(seeds == NULL) {
        printf("Failed to load initial seed list");
        free(seeds);
        return 1;
    }

    /* Find the index of the target seed from the seed data file */
    index = find_seed_index(seeds, target_seed, len);

    if (index == 0) {
        printf("Seed not found in data!");
        return 1;
    }

    /* Declare and initialize the range of seeds to look thru (+/-) target index */
    uint16_t range = 10;

    /* Create an array of new seed structs from range input and copy the new range to s_len*/
    InitialSeed *seedRange = get_seed_range(seeds, len, index, range, &s_len);
    if(seedRange == NULL) {
        printf("Failed to load new seed list");
        free(seeds);
        return 1;
    }

    /* Free the original total list of seeds */
    free(seeds);

    /* Determine the encounter slot data path from game version and area*/
    const char *encounter_data_path = get_encounter_file_path(gv, at.at);

    /* Load slot data in Slot struct array based on input path determined earlier*/
    Slot *slots = load_slots(at, encounter_data_path);

    if (slots == NULL) {
        printf("Failed to load encounter slots");
        free(slots);
        return 1;
    }

    /* Declare a filter struct with values to search for while generating encounters */
    WildFilter wf = {
            20,
            {1, 1},
            {0},
            {0},
            {0},
            {0},
            {0},
            {0},
            {1, 1, 0},
            {0, 0, 1},
            {0}
    };

    /* IV Estimator struct where our only known values are the total stat, nature, level, and mon*/
    IVEstimate target = {
            mon,
            nat,
            level,
            {34, 20, 14, 12, 13, 24},
            {0}
    };

    /* This is probably really stupid, but it sets the nature array to search values*/
    applyNatureToWildFilter(nat, &wf);

    /* Calculate the upper and lower bounds for each stat based on the estimate struct then add them into the filter*/
    applyIVEstimateToWildFilter(&target, &wf);

    clock_t t;
    t = clock();

    /* Create the head node of a linked list to add encounters to */
    wenc_node *head = NULL;

    /* Declare and initialize search parameters*/
    uint32_t init, max;
    init = 0;
    max = 1000;

    /* Generate some wild encounters */
    generateWildEncountersFromSeedList(&head, player, H1, slots, encT, wf, seedRange, s_len, init, max);

    /* Print results of generated encounters from linked list*/
    printWEncounterList(head);

    t = clock() - t;
    double time_taken = (double)t/CLOCKS_PER_SEC;
    printf("\nCompleted in %f seconds", time_taken);

    /* Free all the memory that was created */
    freeWEncList(head);
    free(seedRange);

    return 0;
}