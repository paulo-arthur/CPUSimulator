#include <stdio.h>
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

    instruction_table[0X10] = LDA;
    instruction_table[0X11] = STA;
    instruction_table[0X12] = LDI;

    instruction_table[0x20] = ADD;
    instruction_table[0x21] = SUB;

    // =========================================================
    // PROGRAMA DE TESTE NA RAM
    // =========================================================

    // CENA 1: JMP incondicional
    // O PC começa em 0x8000. Vamos pular direto para 0x8010.
    write_RAM(&ram, 0x8000, 0x01); // Opcode: JMP
    write_RAM(&ram, 0x8001, 0x10); // Low Byte  (0x10)
    write_RAM(&ram, 0x8002, 0x80); // High Byte (0x80)

    // CENA 2: JIC Falso (Carry = 0)
    // O PC vai chegar no 0x8010. O Status Register começa em 0, 
    // então a Flag C está apagada. Ele NÃO deve pular para 0x8025.
    write_RAM(&ram, 0x8010, 0x02); // Opcode: JIC
    write_RAM(&ram, 0x8011, 0x25); // Low Byte  (0x25)
    write_RAM(&ram, 0x8012, 0x80); // High Byte (0x80)

    // Como o JIC falhou, o PC deve apenas ignorar os argumentos 
    // e cair graciosamente na próxima linha: 0x8013.
    // Vamos fazer um JMP aqui para levar para a última fase do teste.
    write_RAM(&ram, 0x8013, 0x01); // Opcode: JMP
    write_RAM(&ram, 0x8014, 0x2F); // Low Byte  (0x30)
    write_RAM(&ram, 0x8015, 0x80); // High Byte (0x80)

    // CENA 3: JIC Verdadeiro (Carry = 1)
    // O PC vai chegar no 0x8030. Nós vamos usar um truque no loop
    // para acender o Carry artificialmente logo antes dessa linha rodar.
    // Como o Carry vai estar aceso, o PC TEM que pular para 0x8042!
    write_RAM(&ram, 0x8030, 0x02); // Opcode: JIC
    write_RAM(&ram, 0x8031, 0x42); // Low Byte  (0x42)
    write_RAM(&ram, 0x8032, 0x80); // High Byte (0x80)

    // Destino final: 0x8042. Vamos colocar um NOP aqui só para ele ler algo em paz.
    write_RAM(&ram, 0x8042, 0x00); // Opcode: NOP

    for(int i = 0; i < 10; i++) {
            printf("--- Ciclo %i ---\n", i);
            printf("PC antes: %4X\n", pc);

            // TRUQUE DE TESTE: Acende a luz do Carry 'na mão' quando chegar na Cena 3
            if (pc == 0x8030) {
                status_register |= 1; // 1 é a máscara da FLAG_C (Bit 0)
                printf(">>> AVISO: Flag C acesa artificialmente! <<<\n");
            }

            byte opcode = read_RAM(&ram, pc);
            pc++;
            
            // Passando o status_register para a instrução!
            // Certifique-se de que o typedef de InstructionHandler aceite esse 4º argumento.
            instruction_table[opcode](&a, &ram, &pc, &status_register);

            printf("Acumulador agora: %i\n", a);
            printf("PC depois: %4X\n\n", pc);

            clock = !clock;
        }
}