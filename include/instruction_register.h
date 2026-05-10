#ifndef INSTRUCTION_REGISTER_H
#define INSTRUCTION_REGISTER_H

#include "byte.h"
#include "stdint.h"
#include "PC.h"
#include "RAM.h"
#include "A.h"
#include "status_register.h"

typedef void (*InstructionHandler)(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);

void NOP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JMP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JIC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JIE(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JNE(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JIN(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void HLT(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);

void LDA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void STA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void LDI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);

void ADD(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void SUB(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void INC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void DEC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void ADI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void SBI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void CMP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);

void AND(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void  OR(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void XOR(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void NOT(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void SHL(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void SHR(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);


#endif