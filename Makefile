# Nome do executável final
TARGET = CS01

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -I./include

# Bibliotecas
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Lista todos os arquivos .c dentro de src/
SRCS = $(wildcard src/*.c)

# Regra principal
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Limpar o executável
clean:
	rm -f $(TARGET)