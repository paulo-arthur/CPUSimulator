#include <stdint.h>

#include "byte.h"

int16_t join_bytes (int8_t HIGH, int8_t LOW)  {
    return (int16_t)((HIGH << 8) | LOW);
};