#ifndef DFF_H
#define DFF_H

#include <stdint.h>

typedef struct {
    int8_t q; //valor guardado
    int8_t prev_clk; //valor do clock passado
} DFF;

void update_DFF (DFF *dff, uint8_t d, uint8_t clk);

#endif