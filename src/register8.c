#include "register8.h"

void update_register(register8 *reg, int8_t data, int clock) {
    for (int i = 0; i < 8; i++) {
        update_DFF(&reg->bits[i], (data >> i) & 1, clock);
    }
}