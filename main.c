#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "include/pokemon.h"
#include "include/ivs.h"
#include "include/seeds.h"
#include "include/rng.h"
#include "include/filters.h"
#include "include/settings.h"

int main(int argc, char* argv[]) {

    /* Make sure argument for settings file was passed */
    if (argc != 2) {
        fprintf(stdout, "Settings ini file path required as arg!\n");
        return EXIT_FAILURE;
    }

    /* Make sure the file actually exists*/
    const char* settings_profile = argv[1];
    if (access(settings_profile, F_OK)) {
        perror("Unable to find ini file!\n");
        return EXIT_FAILURE;
    }

    /* Declare config struct and parse the file with the specified handler*/
    Config cf;
    if (ini_parse(settings_profile, handler, &cf) < 0) {
        perror("Unable to load ini file!\n");
        return EXIT_FAILURE;
    }

    /* Declare player struct */
    Player player;

    /* Declare setting enums to be used from config file */
    Settings settings;

    /* Convert config to player basically */
    player.SID = cf.sid;
    player.TID = cf.tid;

    /* Make sure the loaded values are correct*/
    loadSettings(&cf, &settings);

    /* Search target */
    Pokemon mon = pokemon[20]; // Spearow
    Nature nat = natures[8]; // Impish
    uint8_t level = 13;
    uint32_t target_seed = 0xE585;

    /* Declare the encounter type and the area where the encounter happens */
    EncounterType encT = Grass;
    AreaEntry at = landAreaMap[55]; // Route 10

    /* Create a path to the seed data based on the game version and in game settings */
    const char* fp = get_seed_file_path(settings);
    if (access(fp, F_OK)) {
        perror("Data files missing or not loaded properly!\n");
        return EXIT_FAILURE;
    }

    /* Declare variable to store the amount of seeds that are going to be added to the seeds array*/
    uint64_t len, s_len;
    int index;

    /* Load the seed data based on the file path determined earlier */
    InitialSeed *seeds = load_initial_seeds(fp, &len, None);

    if(seeds == NULL) {
        perror("Failed to load initial seed list");
        free(seeds);
        return EXIT_FAILURE;
    }

    /* Find the index of the target seed from the seed data file */
    index = find_seed_index(seeds, target_seed, len);

    if (index < 0) {
        perror("Seed not found in data!");
        return EXIT_FAILURE;
    }

    /* Declare and initialize the range of seeds to look thru (+/-) target index */
    uint16_t range = 10;

    /* Create an array of new seed structs from range input and copy the new range to s_len*/
    InitialSeed *seedRange = get_seed_range(seeds, len, index, range, &s_len);
    if(seedRange == NULL) {
        perror("Failed to load new seed list");
        free(seeds);
        return EXIT_FAILURE;
    }

    /* Free the original total list of seeds */
    free(seeds);

    /* Determine the encounter slot data path from game version and area*/
    const char *encounter_data_path = get_encounter_file_path(settings.gv, at.at);

    /* Load slot data in Slot struct array based on input path determined earlier*/
    Slot *slots = load_slots(at, encounter_data_path);

    if (slots == NULL) {
        perror("Failed to load encounter slots");
        free(slots);
        return EXIT_FAILURE;
    }

    /* Declare a filter struct with values to search for while generating encounters */
    WildFilter wf = {
            mon.dex - 1,
            level,
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
    max = 100;

    /* Generate some wild encounters */
    generateWildEncountersFromSeedList(&head, player, H1, slots, encT, wf, seedRange, s_len, init, max);

    /* Print results of generated encounters from linked list*/
    printWEncounterList(head);

    t = clock() - t;
    double time_taken = (double)t/CLOCKS_PER_SEC;
    fprintf(stdout, "\nCompleted in %f seconds\n", time_taken);

    /* Free all the memory that was created */
    freeWEncList(head);
    free(seedRange);
    free(slots);

    return EXIT_SUCCESS;
}