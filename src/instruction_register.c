#include "MUX.h"
#include "byte.h"
#include "instruction_register.h"
#include "RAM.h"
#include "A.h"
#include "PC.h"
#include "ALU.h"

#include <stdio.h>

void NOP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    printf("NOP\n");
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
void JIE(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);

    uint16_t mask = -((uint16_t)get_Z_flag(*sr));
    *pc = (*pc & ~mask) | (adress & mask);
}
void JNE(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);

    uint16_t mask = ~-((uint16_t)get_Z_flag(*sr));
    *pc = (*pc & ~mask) | (adress & mask);
}
void JIN(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);

    uint16_t mask = -((uint16_t)get_N_flag(*sr));
    *pc = (*pc & ~mask) | (adress & mask);
}
void HLT(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    set_Q_flag(sr, 1);
}

void LDA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);
    ALU(read_RAM(ram, adress), 0b00000000, 0, sr);
    (*a) = read_RAM(ram, adress);
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
void INC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    (*a) = ALU((*a), 1, 0, sr).RES;
}
void DEC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    (*a) = ALU((*a), 1, 1, sr).RES;
}
void ADI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte arg = read_RAM(ram, (*pc)++);
    (*a) = ALU((*a), arg, 0, sr).RES;
}
void SBI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte arg = read_RAM(ram, (*pc)++);
    (*a) = ALU((*a), arg, 1, sr).RES;
}


void CMP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr) {
    byte low = read_RAM(ram, (*pc)++);
    byte high = read_RAM(ram, (*pc)++);
    uint16_t adress = low | (high << 8);

    ALU(*a, read_RAM(ram, adress), 1, sr);
}