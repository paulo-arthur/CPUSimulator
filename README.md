# CS01 – Simulador de CPU 8-bit

Este projeto implementa uma CPU simples de 8 bits, incluindo:

- Unidade lógica e aritmética (ALU)
- Registradores (A, PC, status)
- Memória RAM
- Unidade de controle baseada em tabela de instruções
- Assembler próprio (Python)

O objetivo é estudar arquitetura de computadores a partir de uma implementação de baixo nível, com controle explícito de bits, flags e fluxo de execução.

---

## Arquitetura

### Tipos principais

- `byte`: inteiro de 8 bits  
- `A`: acumulador (8 bits)  
- `PC`: program counter (16 bits)  
- `STATUS_REGISTER`: flags da CPU  
- `RAM`: memória de 64KB  

---

### Flags

O registrador de status contém:

| Flag | Nome      | Descrição                     |
|------|----------|------------------------------|
| Z    | Zero     | Resultado é zero             |
| N    | Negative | Bit de sinal (bit 7)         |
| C    | Carry    | Carry/borrow da operação     |
| V    | Overflow | Overflow aritmético          |

---

## Organização de Memória

| Região        | Endereço           | Descrição                         |
|--------------|------------------|----------------------------------|
| Zero Page    | 0x0000 – 0x00FF  | Variáveis rápidas                 |
| Stack        | 0x0100 – 0x01FF  | Pilha                            |
| Data RAM     | 0x0200 – 0x7FFF  | Dados gerais                     |
| ROM          | 0x8000 – 0xFFFF  | Código do programa               |

---

## ISA (Instruction Set Architecture)

### Formato geral

- RAM é byte-addressable (8 bits)  
- Endereços são de 16 bits (little endian)  

---

### Grupo 0x0_ – Controle

| Opcode | Instrução | Descrição |
|--------|----------|----------|
| 0x00   | NOP      | Nenhuma operação |
| 0x01   | JMP addr | Salta para endereço |
| 0x02   | JIC addr | Salta se carry = 1 |
| 0x03   | HLT      | Para execução |

---

### Grupo 0x1_ – Dados

| Opcode | Instrução     | Descrição |
|--------|--------------|----------|
| 0x10   | LDA addr     | A ← RAM[addr] |
| 0x11   | STA addr     | RAM[addr] ← A |
| 0x12   | LDI imm      | A ← imediato (8 bits) |

---

### Grupo 0x2_ – ALU

| Opcode | Instrução     | Descrição |
|--------|--------------|----------|
| 0x20   | ADD addr     | A ← A + RAM[addr] |
| 0x21   | SUB addr     | A ← A - RAM[addr] |

---

## ALU

A ALU é implementada bit a bit (ripple-carry), operando com:

- Soma: `A + B`
- Subtração: `A - B` (via complemento de dois)

Ela retorna:

- Resultado (8 bits)
- Flags: Z, N, C, V

As flags são automaticamente atualizadas no `STATUS_REGISTER`.

---

## Assembler

O assembler (`assembler.py`) converte código `.asm` em um arquivo de saída (`a.bin`).

### Características

- Suporte a:
  - Imediatos (`LDI 10`)
  - Endereços (`LDA 0x2000`)
- Saída textual (uma palavra por linha, em hexadecimal)

## Execução

### Compilar

```bash
make
```
Rodar assembler
```bash
python assembler.py
```

## Objetivo

Este projeto não busca performance, mas sim:

Clareza na implementação
Controle total sobre cada operação
Entendimento real de:
ALU
flags
fetch-decode-execute
encoding de instruções
Possíveis Extensões
Suporte a labels no assembler
Saída binária real (.bin)
Debugger (step/run)
Mais instruções (AND, OR, XOR, shifts)
Pilha e chamadas de função
Interrupções
