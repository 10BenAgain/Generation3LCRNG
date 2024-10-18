#include "ivs.h"

void
calculate_stat_totals(Pokemon mon, Nature nt, uint8_t level, const uint8_t *IVs, uint8_t stats[6]) {
    int i;
    stats[0] = (((2 * mon.base_stats[0] + IVs[0]) * level) / 100 ) + (level + 10);
    for (i = 1; i < 6; i++) {
        stats[i] = (((2 * mon.base_stats[i] + IVs[i]) * level / 100 ) + 5) * nature_multiplier_table[nt.key][i - 1];
    }
}

uint16_t
calculate_stat(uint16_t base_s, uint8_t iv, Nature nt, uint8_t level, uint8_t index) {
    uint16_t stat = ((2 * base_s + iv) * level ) / 100;
    if (index)
        return (stat + 5) * nature_multiplier_table[nt.key][index - 1];

    return stat + level + 10;
}

void
get_all_stat_iv_range(IVEstimate *est) {
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 32; j ++) {
            uint16_t st = calculate_stat(est->mon.base_stats[i], j, est->nt, est->level, i);
            est->rs[i][j] = (st == est->stats[i]) ? j : -1;
        }
    }
}

void
get_iv_range(Pokemon mon, Nature nt, uint8_t level, uint16_t stat, uint8_t index, uint8_t result[32]) {
    int i;
    for (i = 0; i < 32; i++) {
        uint16_t st = calculate_stat(mon.base_stats[index], i, nt, level, index);
        if (st == stat) {
            result[i] = i;
        }
    }
}

void
find_bounds(int arr[32], int *l, int *u) {
    int i, j;
    *l = -1;
    for (i = 0; i < 32; i++) {
        if (arr[i] != -1) {
            *l = arr[i];
            break;
        }
    }
    *u = -1;
    for (j = 31; j >= 0; j--) {
        if (arr[j] != -1) {
            *u = arr[j];
            break;
        }
    }
}

void
get_range_difference(int r1[6][32], int r2[6][32], int rte[6][32]) {
    int i, j;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 32; j ++) {
            if (r1[i][j] == r2[i][j]) {
                rte[i][j] = r1[i][j];
            }
            else {
                rte[i][j] = -1;
            }
        }
    }
}