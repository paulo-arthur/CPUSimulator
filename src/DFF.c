#include "DFF.h"
#include "MUX.h"

void update_DFF(DFF *dff, uint8_t d, uint8_t clk) {
    dff->q = MUX(dff->q, d, (clk ^ dff->prev_clk) & clk); //escolhe entre o valor que era e o valor na entrada atual baseado na codição do clock estar mudando (diferente do anterior e se ele é 1)
    dff->prev_clk = clk;
}