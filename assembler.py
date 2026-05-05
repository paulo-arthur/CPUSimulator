with open('main.asm', 'r') as file:
    content = file.read().upper()

content = content.split("\n")

START_ADRESS = 0x8000

LABELS = []
RAM_SHADOW = ["NOP"] * 65536

CODE_TO_BIN_REFERENCE = {
    "NOP": 0x0000,
    "JMP": 0X0100,
    "JIC": 0X0200,
    "HLT": 0X0300,

    "LDA": 0x1000,
    "STA": 0X1100,
    "LDI": 0X1200,

    "ADD": 0X2000,
    "SUB": 0X2100,
}

pc = 0

for i in range(len(content)):
    line = content[i].strip().split()

    if line[0].endswith(":"):
        LABELS.append(i)
        continue
    
    opcode = CODE_TO_BIN_REFERENCE[line[0]]

    RAM_SHADOW[START_ADRESS + pc] = f"{opcode:04X}"
    pc += 1
    
    for j in range(1, len(line[1:]) + 1):
        RAM_SHADOW[START_ADRESS + pc] = f"{int(line[j].replace(',', '')):04X}"
        pc += 1

    content[i] = line



for i in RAM_SHADOW[32768:32768 + 15]:
    print(i)