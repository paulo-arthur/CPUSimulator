#include "MUX.h"
#include "byte.h"
#include "instruction_register.h"
#include "RAM.h"
#include "A.h"
#include "PC.h"
#include "ALU.h"

#include <stdio.h>

void NOP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    printf("NO\n");
}
void UNK(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    printf("Nada foi feito\n");
}
void LDA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);
    ALU(read_RAM(ram, adress), 0b00000000, 0, sr);
    (*a) = read_RAM(ram, adress);
}
void ADD(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);
    (*a) = ALU((*a), read_RAM(ram, adress), 0, sr).RES;
}
void SUB(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);
    (*a) = ALU((*a), read_RAM(ram, adress), 1, sr).RES;
}
void STA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);

    write_RAM(ram, adress, *a);
}
void LDI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte arg = read_RAM(ram, (*pc)++);
    ALU(arg, 0b00000000, 0, sr);
    *a = arg;
}
void JMP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);
    *(pc) = adress;
}
void JIC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);
    
    uint16_t mask = -((uint16_t)get_C_flag(*sr));
    
    *pc = (*pc & ~mask) | (adress & mask);
};