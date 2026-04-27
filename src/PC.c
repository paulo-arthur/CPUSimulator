#include <stdint.h>
#include "PC.h"

void increase_PC(uint16_t *pc) {
    (*pc)++;
}

void jump_PC(uint16_t *pc, uint16_t adr) {
    (*pc) = adr;
}   