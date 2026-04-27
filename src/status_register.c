#include "status_register.h"
#include "byte.h"

byte get_C_flag(STATUS_REGISTER sr) {
    return (sr & FLAG_C) >> 0; 
}

void set_C_flag(STATUS_REGISTER *sr, byte value) {
    *sr = (*sr & ~FLAG_C) | ((!!value) << 0);
}

byte get_Z_flag(STATUS_REGISTER sr) {
    return (sr & FLAG_Z) >> 1;
}
void set_Z_flag(STATUS_REGISTER *sr, byte value) {
    *sr = (*sr & ~FLAG_Z) | ((!!value) << 1);
}

byte get_N_flag(STATUS_REGISTER sr) {
    return (sr & FLAG_N) >> 2;
}
void set_N_flag(STATUS_REGISTER *sr, byte value) {
    *sr = (*sr & ~FLAG_N) | ((!!value) << 2);
}

byte get_V_flag(STATUS_REGISTER sr) {
    return (sr & FLAG_V) >> 3;
}
void set_V_flag(STATUS_REGISTER *sr, byte value) {
    *sr = (*sr & ~FLAG_V) | ((!!value) << 3);
}