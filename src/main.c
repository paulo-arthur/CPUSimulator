#include <stdio.h>
#include <stdint.h>

#include "ALU.h"
#include "MUX.h"

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
}