#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define GBA_FPS 59.7275
#define NDS_FPS 59.6555
#define NEW3DS  59.8261
#define OLD3DS  59.8261
#define FPS60   60

#define MINIMUM_INTRO_TIME      34744
#define MAXIMUM_INTRO_TIME      75640

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
    int i, a, t;

    i = first[0] - second[0];
    a = first[1] - second[1];
    t = first[2] - second[2];

    output[0] = first[0] + i;
    output[1] = first[1] + a;
    output[2] = first[2] + t;
}

int main() {
    uint32_t intro, intro2, adv, adv2;
    intro = 36000;
    adv = 1600;

    uint32_t out[3] = {0, 0, 0};
    uint32_t out2[3] = {0, 0, 0};
    uint32_t out3[3] = {0, 0, 0};

    calculateInitialTimerNDS(intro, adv, out);

    printf("%d/%d (%d)\n", out[0], out[1], out[2]);

    intro2 = 35123;
    adv2 = 1234;

    calculateInitialTimerNDS(intro2, adv2, out2);
    printf("%d/%d (%d)\n", out2[0], out2[1], out2[2]);
    calculateTimerDifference(out, out2, out3);
    printf("%d/%d (%d)\n", out3[0], out3[1], out3[2]);

    return 0;
}