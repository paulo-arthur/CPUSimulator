#ifndef RAM_H
#define RAM_H

#include <stdint.h>

#include "byte.h"

#define RAM_SIZE 65536

typedef struct
{
    uint8_t data[RAM_SIZE];
} RAM;

void init_RAM(RAM *mem);

byte read_RAM (RAM *mem, uint16_t adress);

void write_RAM(RAM *mem, uint16_t adress, uint8_t value);

#endif