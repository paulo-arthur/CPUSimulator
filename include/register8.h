#ifndef REGISTER8_H
#define REGISTER8_H

#include <stdint.h>

#include "DFF.h"
#include "byte.h"

typedef DFF register8[8];

void update_register(register8 reg, int8_t data, int clock);
byte get_full_byte(register8 reg);


#endif