#ifndef REGISTER8_H
#define REGISTER8_H

#include <stdint.h>
#include "DFF.h"

typedef struct
{
    DFF bits[8];
} register8;

void update_register(register8 *reg, int8_t data, int clock);

#endif