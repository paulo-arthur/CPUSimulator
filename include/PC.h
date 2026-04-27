#ifndef PC_H
#define PC_H

#include <stdint.h>

typedef uint16_t PC;

void increase_PC(uint16_t *pc);
void jump_PC(uint16_t *pc, uint16_t adr);

#endif