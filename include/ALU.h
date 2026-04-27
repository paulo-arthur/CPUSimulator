#ifndef ALU_H
#define ALU_H

#include <stdint.h>
#include "byte.h"
#include "status_register.h"

typedef struct
{
    uint8_t RES; //result
    uint8_t Z; //zero
    uint8_t N; //negative
    uint8_t C; //carrier
    uint8_t V; //overflow

} ALU_OUTPUT;

ALU_OUTPUT ALU(byte A, byte B, byte A_S, STATUS_REGISTER *sr);

#endif