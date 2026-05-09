#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ALU.h"
#include "MUX.h"
#include "DFF.h"
#include "register8.h"
#include "RAM.h"
#include "A.h"
#include "PC.h"
#include "instruction_register.h"
#include "status_register.h"

int8_t dec2bin (int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%i", n >> i & 1);
        if (!(i % 8)) printf(" ");
    }
    printf("\n");

    return (int8_t)n;
}

int main() {
    /*
    ALU_OUTPUT a = ALU(127, 1, 1);
    printf("RES: %.8b\n", (uint8_t)a.RES);
    printf("RES: %i\n", a.RES);
    printf("Z  : %.8b\n", a.Z);
    printf("N  : %.8b\n", a.N);
    printf("C  : %.8b\n", a.C);
    printf("V  : %.8b\n", a.V);
    return 0;
    */

    /*
    byte: int8_t representado em 0bXXXXXXXX;
    DFF: int8_t q (valor guardado) e int8_t prev_clk;
    register8: DFF bits[8];
    RAM: int8_t data[RAM_SIZE];
    A: uint8_t;
    PC: uint16_t;
    STATUS_REGISTER: register8 0b####CZNV; 
    */

    int8_t clock = 0;
    RAM ram;
    init_RAM(&ram);
    A a = 0;
    PC pc = 0x8000;
    InstructionHandler instruction_table[256];
    STATUS_REGISTER status_register = 0;

    for (int i = 0; i < 256; i++) {
        instruction_table[i] = UNK;
    }

    instruction_table[0x00] = NOP;
    instruction_table[0x01] = JMP;
    instruction_table[0x02] = JIC;
    instruction_table[0x03] = JIE;
    instruction_table[0x04] = JNE;
    instruction_table[0x05] = JIN;
    instruction_table[0x0F] = HLT;

    instruction_table[0X10] = LDA;
    instruction_table[0X11] = STA;
    instruction_table[0X12] = LDI;

    instruction_table[0x20] = ADD;
    instruction_table[0x21] = SUB;
    instruction_table[0x22] = CMP;

    FILE* file = fopen("a.bin", "r");
    char line[256];

    int line_counter = 0;
    while (fgets(line, sizeof(line), file)) {
        write_RAM(&ram, line_counter++, (uint8_t)strtol(line, NULL, 0));
    }
    fclose(file);

    int i = 0;
    while(!get_Q_flag(status_register)) {
            printf("--- Ciclo %i ---\n", i);
            printf("PC antes: %4X\n", pc);

            byte opcode = read_RAM(&ram, pc++);

            instruction_table[opcode](&a, &ram, &pc, &status_register);

            printf("Acumulador agora: %i\n", a);
            printf("PC depois: %4X\n\n", pc);
            printf("Flags \nZ: %X\nN: %X\nC: %X\nV: %X\n"
                , get_Z_flag(status_register)
                , get_N_flag(status_register)
                , get_C_flag(status_register)
                , get_V_flag(status_register));

            clock = !clock;
            i++;
        }
}