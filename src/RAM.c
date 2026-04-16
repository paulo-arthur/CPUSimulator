#include <stdint.h>
#include <string.h>

#include "byte.h"
#include "RAM.h"

void init_RAM(RAM *mem) {
    memset(mem->data, 0, RAM_SIZE);
};

byte read_RAM (RAM *mem, uint16_t adress) {
    return mem->data[adress];
};

void write_RAM(RAM *mem, uint16_t adress, uint8_t value) {
    mem->data[adress] = value;
};