#ifndef TIMERS_H
#define TIMERS_H

#include <math.h>
#include <stdint.h>
#include "constants.h"

void calculateInitialTimerNDS(uint32_t intro, uint32_t advances, uint32_t output[3]);
void calculateTimerDifference(uint32_t first[3], uint32_t second[3], uint32_t output[3]);

#endif
