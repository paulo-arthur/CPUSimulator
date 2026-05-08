with open('main.asm', 'r') as file:
    content = file.read().upper()

content = content.split("\n")

START_ADRESS = 0x8000

CODE_TO_BIN = {
    "NOP": {"opcode": 0x00, "mode": "NONE"},
    "JMP": {"opcode": 0x01, "mode": "ADDR16"},
    "JIC": {"opcode": 0x02, "mode": "ADDR16"},
    "HLT": {"opcode": 0x03, "mode": "NONE"},

    "LDA": {"opcode": 0x10, "mode": "ADDR16"},
    "STA": {"opcode": 0x11, "mode": "ADDR16"},
    "LDI": {"opcode": 0x12, "mode": "IMM8"},

    "ADD": {"opcode": 0x20, "mode": "ADDR16"},
    "SUB": {"opcode": 0x21, "mode": "ADDR16"},
}

LABELS = []

RAM = ["00"] * 65536

pc = 0

for p in range(len(content)):
    line = content[p].split()
    if not len(line) == 0 and line[0].endswith(":"):
        LABELS.append({
            "label": line[0].replace(":", ""),
            "adr": START_ADRESS + p
        })
        continue

for i in range(len(content)):
    line = content[i].split()

    if not line or line[0].endswith(":"):
        continue
    
    if line[0] in CODE_TO_BIN:
        inst = CODE_TO_BIN[line[0]]
        opcode = inst["opcode"]
        mode = inst["mode"]
    else:
        raise Exception(f"Instrução inválida: {line[0]}")

    RAM[START_ADRESS + pc] = f"{opcode:02X}"
    pc += 1

    args = line[1:]

    if mode == "NONE":
        if len(args) != 0:
            raise Exception(f"{line[0]} não recebe argumentos")
        continue

    if len(args) != 1:
        raise Exception(f"{line[0]} precisa de 1 argumento")
    
    if not args[0].isnumeric():
        for l in LABELS:
            if l["label"] == args[0]:
                arg = l["adr"]
    else:
        arg = int(args[0], 0)

    if mode == "IMM8":
        RAM[START_ADRESS + pc] = f"{arg & 0xFF:02X}"
        pc += 1
    elif mode == "ADDR16":
        low = arg & 0xFF
        high = (arg >> 8) & 0xFF
        RAM[START_ADRESS + pc] = f"{low:02X}"
        pc += 1
        RAM[START_ADRESS + pc] = f"{high:02X}"
        pc += 1

for i in range(len(RAM)):
    RAM[i] ="0x" + RAM[i] + '\n'

with open("a.bin", "w") as output:
    output.writelines(RAM)