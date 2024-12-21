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

typedef struct {
    const char* command;
    void (*handler)();
} Command;

void listHandler(const char* arg1, const char* arg2) {
    if (!strcmp(arg1, "natures")) {
        PokemonListNatures();
    } else {
        fprintf(stderr, "Unknown subcommand: %s\n", arg1);
    }
    if (!strcmp(arg1, "locations")) {
        if (!strcmp(arg2, "grass")) {
            LocationListFromEncType(Grass);
        } else if (!strcmp(arg2, "water")) {
            LocationListFromEncType(Water);
        } else if (!strcmp(arg2, "rock")) {
            LocationListFromEncType(RockSmash);
        } else
            fprintf(stderr, "Unable to match location area type\n");
    }
}

int main(int argc, char** argv) {
    if (!strcmp(argv[1], "list")) {
        if (!strcmp(argv[2], "Natures")) {
            PokemonListNatures();
        } else if (!strcmp(argv[2], "locations")) {
            if (!strcmp(argv[3], "Grass")) {
                LocationListFromEncType(Grass);
            } else if (!strcmp(argv[3], "Water")) {
                LocationListFromEncType(Water);
            } else if (!strcmp(argv[3], "Rock")) {
                LocationListFromEncType(RockSmash);
            } else
                fprintf(stderr, "Unable to match location area type\n");
                return EXIT_FAILURE;
        } else {
            fprintf(stderr, "Unable to find that command:\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    char* path = "settings.ini";
    char* inputMon = NULL;
    char* inputNature = NULL;
    char* lend;
    int llevel = 0;
    uint32_t inputSeed = 0;
    int wflag = 0;
    int sflag = 0;
    long l;

    int opt;
    while ((opt = getopt(argc, argv, "I:m:l:n:t:ws")) != -1) {
        switch (opt) {
            case 'I':
                path = optarg;
                break;
            case 'm':
                inputMon = optarg;
                break;
            case 'l':
                l = strtol(optarg, &lend, 10);
                if (lend == optarg) {
                    fprintf(stderr, "Invalid level input!\n");
                } else if (l > 100 || l < 5) {
                    fprintf(stderr, "Level must be between 5 an 100\n");
                } else
                    llevel = (int)l;
                break;
            case 'n':
                 if (PokemonGetNatureIndex(optarg) > 0) {
                     inputNature = optarg;
                 } else fprintf(stderr, "Invalid nature string provided\n");
                break;
            case 't':
                l = strtol(optarg, &lend, 16);
                if (lend == optarg) {
                    fprintf(stderr, "Invalid level input!\n");
                } else
                    inputSeed = (uint32_t)l;
                break;
            case 'w':
                if (sflag) {
                    fprintf(stderr, "Only one encounter type can be selected at once ( -w or -s)\n");
                    exit(EXIT_FAILURE);
                } else {
                    wflag = 1;
                }
                break;
            case 's':
                if (wflag) {
                    fprintf(stderr, "Only one encounter type can be selected at once ( -w or -s)\n");
                    exit(EXIT_FAILURE);
                } else {
                    sflag = 1;
                }
                break;
            default:
                fprintf(stderr, "Unknown option: %c\n", optopt);
                exit(EXIT_FAILURE);
        }
    }

    int m_index = PokemonSearchIndex(inputMon);

    if (m_index > 0) {
        fprintf(stdout, "Mon index = %d, Level = %d, Nature = %s (%d), Target Seed = %X\n", m_index, llevel, inputNature,
                PokemonGetNatureIndex(inputNature), inputSeed);
    }
    /* Make sure the file actually exists*/
    if (access(path, F_OK)) {
        perror("Unable to find ini file!\n");
        return EXIT_FAILURE;
    }

    /* Declare config struct and parse the file with the specified handler*/
    Config cf;
    if (ini_parse(path, handler, &cf) < 0) {
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
    AreaEntry at = LAND_AREA_MAP[55]; // Route 10

    /* Create a path to the seed data based on the game version and in game settings */
    const char* fp = SeedGetFilePath(settings);
    if (access(fp, F_OK)) {
        perror("Data files missing or not loaded properly!\n");
        return EXIT_FAILURE;
    }

    /* Declare variable to store the amount of seeds that are going to be added to the seeds array*/
    uint64_t len, s_len;
    int index;

    /* Load the seed data based on the file path determined earlier */
    InitialSeed *seeds = SeedLoadInitial(fp, &len, None);

    if(seeds == NULL) {
        perror("Failed to load initial seed list");
        free(seeds);
        return EXIT_FAILURE;
    }

    /* Find the index of the target seed from the seed data file */
    index = SeedFindIndex(seeds, target_seed, len);

    if (index < 0) {
        perror("Seed not found in data!");
        return EXIT_FAILURE;
    }

    /* Declare and initialize the range of seeds to look thru (+/-) target index */
    uint16_t range = 10;

    /* Create an array of new seed structs from range input and copy the new range to s_len*/
    InitialSeed *seedRange = SeedGetSeedRange(seeds, len, index, range, &s_len);
    if(seedRange == NULL) {
        perror("Failed to load new seed list");
        free(seeds);
        return EXIT_FAILURE;
    }

    /* Free the original total list of seeds */
    free(seeds);

    /* Determine the encounter slot data path from game version and area*/
    const char *encounter_data_path = LocationGetEncounterFilePath(settings.gv, at.at);

    /* Load slot data in Slot struct array based on input path determined earlier*/
    Slot *slots = LocationLoadEncounterSlots(at, encounter_data_path);

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
    FilterApplyNatureToWild(nat, &wf);

    /* Calculate the upper and lower bounds for each stat based on the estimate struct then add them into the filter*/
    FilterApplyIVEstimateToWild(&target, &wf);

    clock_t t;
    t = clock();

    /* Create the head node of a linked list to add encounters to */
    wenc_node *head = NULL;

    /* Declare and initialize search parameters*/
    uint32_t init, max;
    init = 0;
    max = 100;

    /* Generate some wild encounters */
    FilterGenerateWildEncountersFromSeedList(&head, player, H1, slots, encT, wf, seedRange, s_len, init, max);

    /* Print results of generated encounters from linked list*/
    FilterPrintWEncounterList(head);

    t = clock() - t;
    double time_taken = (double)t/CLOCKS_PER_SEC;
    fprintf(stdout, "\nCompleted in %f seconds\n", time_taken);

    /* Free all the memory that was created */
    FilterFreeWEncList(head);
    free(seedRange);
    free(slots);

    return EXIT_SUCCESS;
}