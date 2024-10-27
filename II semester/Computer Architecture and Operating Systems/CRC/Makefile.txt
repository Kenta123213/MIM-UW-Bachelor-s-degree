# Variables
ASM = nasm
LD = ld
ASMFLAGS = -f elf64 -w+all -w+error
LDFLAGS = --fatal-warnings
SRC = crc.asm
OBJ = crc.o
OUT = crc

# Default target
all: $(OUT)

# Rule to assemble the .asm file
$(OBJ): $(SRC)
	$(ASM) $(ASMFLAGS) -o $(OBJ) $(SRC)

# Rule to link the object file
$(OUT): $(OBJ)
	$(LD) $(LDFLAGS) -o $(OUT) $(OBJ)

# Clean target to remove object and binary files
clean:
	rm -f $(OBJ) $(OUT)

# Phony targets
.PHONY: all clean
