#include "../include/timers.h"

uint32_t adv2ms(double fr, uint32_t advances) {
    return (uint32_t)(round( 1 / fr * 1000 * advances));
}

void calculateInitialTimerNDS(uint32_t intro, uint32_t advances, uint32_t output[3]) {
    if (intro < MINIMUM_INTRO_TIME || intro > MAXIMUM_INTRO_TIME) return;

    output[0] = intro;                           // Intro MS

    uint32_t adv_ms = adv2ms(NDS_FPS, advances);
    if (adv_ms <= 0) return;

    output[1] = adv_ms;                         // Advances in MS
    output[2] = output[0] + output[1];          // Total time
}

void calculateTimerDifference(uint32_t first[3], uint32_t second[3], uint32_t output[3]) {
    output[0] = first[0] + (first[0] - second[0]); // Intro MS
    output[1] = first[1] + (first[1] - second[1]); // Advances MS
    output[2] = first[2] + (first[2] - second[2]); // Total MS
}