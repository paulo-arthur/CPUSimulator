with open('main.asm', 'r') as file:
    content = file.read().upper()

content = content.split("\n")

START_ADDRESS = 0x8000

CODE_TO_BIN = {
    "NOP": {"opcode": 0x00, "mode": "NONE"},
    "JMP": {"opcode": 0x01, "mode": "ADDR16"},
    "JIC": {"opcode": 0x02, "mode": "ADDR16"},
    "JIE": {"opcode": 0x03, "mode": "ADDR16"},
    "JNE": {"opcode": 0x04, "mode": "ADDR16"},
    "JIN": {"opcode": 0x05, "mode": "ADDR16"},
    "HLT": {"opcode": 0x0F, "mode": "NONE"},

    "LDA": {"opcode": 0x10, "mode": "ADDR16"},
    "STA": {"opcode": 0x11, "mode": "ADDR16"},
    "LDI": {"opcode": 0x12, "mode": "IMM8"},

    "ADD": {"opcode": 0x20, "mode": "ADDR16"},
    "SUB": {"opcode": 0x21, "mode": "ADDR16"},
    "INC": {"opcode": 0x22, "mode": "NONE"},
    "DEC": {"opcode": 0x23, "mode": "NONE"},
    "ADI": {"opcode": 0x24, "mode": "IMM8"},
    "SBI": {"opcode": 0x25, "mode": "IMM8"},
    "CMP": {"opcode": 0x2F, "mode": "ADDR16"},

    "AND": {"opcode": 0x30, "mode": "ADDR16"},
     "OR": {"opcode": 0x31, "mode": "ADDR16"},
    "XOR": {"opcode": 0x32, "mode": "ADDR16"},
    "NOT": {"opcode": 0x33, "mode": "NONE"},
    "SHL": {"opcode": 0x34, "mode": "NONE"},
    "SHR": {"opcode": 0x35, "mode": "NONE"},
}

#TODO: atualizar ISA.txt quanto ao INC e DEC

LABELS = []

RAM = ["00"] * 65536

pc = START_ADDRESS
label_pre_pc = START_ADDRESS

for p in range(len(content)):
    line = content[p].split()

    if not line:
        continue

    if line[0].endswith(":"):
        LABELS.append({
            "label": line[0].replace(":", ""),
            "adr": label_pre_pc
        })
        continue 

    label_pre_pc += 1

    try:
        if CODE_TO_BIN[line[0]]["mode"] == "ADDR16":
            label_pre_pc += 2
        elif CODE_TO_BIN[line[0]]["mode"] == "IMM8":
            label_pre_pc += 1
    except ValueError:
        pass

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

    RAM[pc] = f"{opcode:02X}"
    pc += 1

    args = line[1:]

    if mode == "NONE":
        if len(args) != 0:
            raise Exception(f"{line[0]} não recebe argumentos")
        continue

    if len(args) != 1:
        raise Exception(f"{line[0]} precisa de 1 argumento")

    try:
        arg = int(args[0], 0)
    except:
        was_label_found = False
        for l in LABELS:
            if l["label"] == args[0]:
                arg = l["adr"]
                was_label_found = True
        
        if not was_label_found:
            print("Label not found.")

    if mode == "IMM8":
        RAM[pc] = f"{arg & 0xFF:02X}"
        pc += 1
    elif mode == "ADDR16":
        low = arg & 0xFF
        high = (arg >> 8) & 0xFF
        RAM[pc] = f"{low:02X}"
        pc += 1
        RAM[pc] = f"{high:02X}"
        pc += 1

for i in range(len(RAM)):
    RAM[i] ="0x" + RAM[i] + '\n'

with open("a.bin", "w") as output:
    output.writelines(RAM)