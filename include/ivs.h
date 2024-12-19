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

void IVsFindBounds(int arr[32], int *l, int *u);
void IVsGetRangeDifference(int r1[6][32], int r2[6][32], int rte[6][32]);
void IVsGetIVRange(Pokemon mon, Nature nt, uint8_t level, uint16_t stat, uint8_t index, uint8_t result[32]);
void IVsGetAllStatRanges(IVEstimate *est);

#endif
