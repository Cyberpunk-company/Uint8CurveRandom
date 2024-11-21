#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define UNUSED(x) (void)(x)
/**
  Curves callbacks
*/
uint8_t distrib_lin_inc(uint8_t value, uint8_t max) {
    UNUSED(max);
    return value + 1;
}
uint8_t distrib_lin_dec(uint8_t value, uint8_t max) {
    return max - value;
}
uint8_t distrib_sym_bell(uint8_t value, uint8_t max) {
    return value <= max / 2 ? value + 1 : max - value;
}
uint8_t distrib_exp_inc(uint8_t value, uint8_t max) {
    return 1 + (value * value) / (max - 1);
  }
uint8_t distrib_exp_dec(uint8_t value, uint8_t max) {
    return 1 + ((max - 1 - value) * (max - 1 - value)) / (max - 1);
  }
uint8_t distrib_flat(uint8_t value, uint8_t max) {
    UNUSED(max);
    UNUSED(value);
    return 1;
}
uint8_t distrib_tri(uint8_t value, uint8_t max) {
    return value <= max / 2 ? 2 * value + 1 : 2 * (max - value - 1) + 1;
}

/**
  Curve driven random generator
*/
uint8_t rand_curve(uint8_t (*w_func)(uint8_t, uint8_t), uint8_t max) {
    uint16_t total = 0;

    for (uint8_t i = 0; i < max; i++)
        total += w_func(i, max);

    uint16_t rd = rand() % total;
    uint16_t cumul = 0;

    for (uint8_t i = 0; i < max; i++) {
        cumul += w_func(i, max);
        if (rd < cumul) return i;
    }

    return 0;
}

/**
  Simple bargraph dusplay helper
*/
void show_bargraph(int value, int max) {
    const char *bars[] = {
        "\xe2\x96\x81", // ▁
        "\xe2\x96\x82", // ▂
        "\xe2\x96\x83", // ▃
        "\xe2\x96\x84", // ▄
        "\xe2\x96\x85", // ▅
        "\xe2\x96\x86", // ▆
        "\xe2\x96\x87"  // ▇
    };
    if (value < 0) value = 0;
    if (value > max) value = max;
    int levels = 7;
    int index = (value * (levels - 1)) / max;
    printf("%s", bars[index]);
}

int main() {

    srand(time(NULL));
    int i = 0;
    /*
        Display curves:
    */
    for(i=0; i<15; i++){
      show_bargraph(distrib_lin_inc(i, 15), 15);
    }
    printf("\n");

    for(i=0; i<15; i++){
      show_bargraph(distrib_lin_dec(i, 15), 15);
    }
    printf("\n");

    for(i=0; i<15; i++){
      show_bargraph(distrib_sym_bell(i, 15), 15);
    }
    printf("\n");

    for(i=0; i<15; i++){
      show_bargraph(distrib_exp_inc(i, 15), 15);
    }
    printf("\n");

    for(i=0; i<15; i++){
      show_bargraph(distrib_exp_dec(i, 15), 15);
    }
    printf("\n");

    for(i=0; i<15; i++){
      show_bargraph(distrib_flat(i, 15), 15);
    }
    printf("\n");

    for(i=0; i<15; i++){
      show_bargraph(distrib_tri(i, 15), 15);
    }
    printf("\n");
    /*
        Examples:
    */
    for (i = 0; i < 10; i++) {
        printf("%u\n", rand_curve(distrib_exp_dec, 20));
    }
    printf("\n");

    return 0;
}
