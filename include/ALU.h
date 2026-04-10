#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef struct
{
    int8_t RES; //result
    uint8_t Z; //zero
    uint8_t N; //negative
    uint8_t C; //carrier
    uint8_t V; //overflow

} ALU_OUTPUT;

ALU_OUTPUT ALU(int A, int B, int A_S);

#endif