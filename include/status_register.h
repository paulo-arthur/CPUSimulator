#ifndef STATUS_REGISTER_H
#define STATUS_REGISTER_H

#include <stdint.h>
#include "byte.h"

#define FLAG_C (1 << 0) // Bit 0 (0000 0001)
#define FLAG_Z (1 << 1) // Bit 1 (0000 0010)
#define FLAG_N (1 << 2) // Bit 2 (0000 0100)
#define FLAG_V (1 << 3) // Bit 3 (0000 1000)

typedef uint8_t STATUS_REGISTER;

byte get_C_flag(STATUS_REGISTER sr);
void set_C_flag(STATUS_REGISTER *sr, byte value);

byte get_Z_flag(STATUS_REGISTER sr);
void set_Z_flag(STATUS_REGISTER *sr, byte value);

byte get_N_flag(STATUS_REGISTER sr);
void set_N_flag(STATUS_REGISTER *sr, byte value);

byte get_V_flag(STATUS_REGISTER sr);
void set_V_flag(STATUS_REGISTER *sr, byte value);

#endif