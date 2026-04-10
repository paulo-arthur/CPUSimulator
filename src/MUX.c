#include <stdint.h>

int8_t MUX (int a, int b, int s) {
    return (a & !s) | (b & s);
}