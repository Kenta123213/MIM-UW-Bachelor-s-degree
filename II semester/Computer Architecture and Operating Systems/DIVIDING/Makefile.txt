# Kompilator i flagi
NASM = nasm
NASM_FLAGS = -f elf64 -w+all -w+error

GCC = gcc
GCC_CFLAGS = -Wall -Wextra -std=c17 -O2
GCC_LDFLAGS = -z noexecstack

# Pliki źródłowe i wynikowe
ASM_SOURCE = mdiv.asm
ASM_OBJECT = mdiv.o

C_SOURCE = mdiv_example.c
C_OBJECT = mdiv_example.o

EXECUTABLE = mdiv_example

# Cele makefile
.PHONY: all clean

all: $(EXECUTABLE)

$(ASM_OBJECT): $(ASM_SOURCE)
	$(NASM) $(NASM_FLAGS) -o $@ $<

$(C_OBJECT): $(C_SOURCE)
	$(GCC) $(GCC_CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(C_OBJECT) $(ASM_OBJECT)
	$(GCC) $(GCC_LDFLAGS) -o $@ $^

clean:
	rm -f $(ASM_OBJECT) $(C_OBJECT) $(EXECUTABLE)
