#include <stdint.h>
#include "byte.h"

byte MUX (byte f, byte t, byte s) {
    return (f & ~(-s)) | (t & -s);
}