#ifndef IVS_H
#define IVS_H

#include <stdint.h>
#include "pokemon.h"

typedef struct {
    Pokemon mon;
    Nature nt;
    uint8_t level;
    uint16_t stats[6];
    int rs[6][32];
} IVEstimate;

void find_bounds(int arr[32], int *l, int *u);
void get_range_difference(int r1[6][32], int r2[6][32], int rte[6][32]);
void get_iv_range(Pokemon mon, Nature nt, uint8_t level, uint16_t stat, uint8_t index, uint8_t result[32]);
void get_all_stat_iv_range(IVEstimate *est);

#endif
