#include <stdio.h>
#include <stdint.h>

#include "ALU.h"
#include "MUX.h"
#include "DFF.h"
#include "register8.h"

int8_t dec2bin (int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%i", n >> i & 1);
        if (!(i % 8)) printf(" ");
    }
    printf("\n");

    return (int8_t)n;
}

int main() {
    /*
    ALU_OUTPUT a = ALU(127, 1, 1);
    printf("RES: %.8b\n", (uint8_t)a.RES);
    printf("RES: %i\n", a.RES);
    printf("Z  : %.8b\n", a.Z);
    printf("N  : %.8b\n", a.N);
    printf("C  : %.8b\n", a.C);
    printf("V  : %.8b\n", a.V);
    return 0;
    */

    /*
    byte: int8_t representado em 0bXXXXXXXX;
    DFF: int8_t q (valor guardado) e int8_t prev_clk;
    register8: DFF bits[8];
    */

    int8_t clock = 0;

    register8 reg01 = {0};

    for(int i = 0; i < 40; i++) {
        printf("%.8b\n", (uint8_t)get_full_byte(reg01));

        byte output = ALU(get_full_byte(reg01), 0b00000001, 0b00000001).RES;
        update_register(reg01, output, clock);

        clock = !clock;
    }
}