#include <stdint.h>

#include "byte.h"

int16_t join_bytes (uint8_t HIGH, uint8_t LOW)  {
    return (int16_t)((HIGH << 8) | LOW);
};