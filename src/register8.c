#include "register8.h"

void update_register(register8 reg, int8_t data, int clock) {
    update_DFF(&reg[0], (data >> 0) & 1, clock);
    update_DFF(&reg[1], (data >> 1) & 1, clock);
    update_DFF(&reg[2], (data >> 2) & 1, clock);
    update_DFF(&reg[3], (data >> 3) & 1, clock);
    update_DFF(&reg[4], (data >> 4) & 1, clock);
    update_DFF(&reg[5], (data >> 5) & 1, clock);
    update_DFF(&reg[6], (data >> 6) & 1, clock);
    update_DFF(&reg[7], (data >> 7) & 1, clock);
}

byte get_full_byte(register8 reg) {
    byte out = 0b00000000;
    out |= (reg[0].q << 0);
    out |= (reg[1].q << 1);
    out |= (reg[2].q << 2);
    out |= (reg[3].q << 3);
    out |= (reg[4].q << 4);
    out |= (reg[5].q << 5);
    out |= (reg[6].q << 6);
    out |= (reg[7].q << 7);

    return out;
}
