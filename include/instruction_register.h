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
void UNK(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void LDA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void ADD(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void SUB(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void STA(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void LDI(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JMP(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);
void JIC(A *a, RAM *ram, PC *pc, STATUS_REGISTER *sr);

#endif