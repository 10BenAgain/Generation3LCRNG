#include <stdio.h>
#include "src/pokemon.h"
#include <stdlib.h>
#include <sys/types.h>


int main(int argc, char ** argv) {

    if (argc != 7) {
        return EXIT_FAILURE;
    }

    int level = strtol(argv[1], NULL, 10);
    Nature nature = natures[strtol(argv[1], NULL, 10)];
    int base_stat = strtol(argv[3], NULL, 10);
    int stat_total = strtol(argv[4], NULL, 10);
    int stat_num = strtol(argv[5], NULL, 10);
    int evs = strtol(argv[6], NULL, 10);

    u_int8_t* ivs = get_iv_range(level, nature, base_stat, stat_total, stat_num, evs);

    fprintf(stdout, "{%d, %d}\n", ivs[0], ivs[1]);
    free(ivs);

    return EXIT_SUCCESS;
}
