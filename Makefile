# Nome do executável final
TARGET = CS01

# Compilador
CC = gcc

# Flags de compilação (-I./include diz ao GCC para buscar headers lá)
CFLAGS = -Wall -I./include

# Lista todos os arquivos .c dentro de src/
SRCS = $(wildcard src/*.c)

# Regra principal
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Limpar o executável
clean:
	rm -f $(TARGET)