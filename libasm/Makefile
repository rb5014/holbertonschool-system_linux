SRC_ASM = 7-puts.asm
SRC_MAIN = tests/7-main.c

all: main_obj asm_obj
	gcc *.o
	make clean

main_obj:
	gcc -Wall -Wextra -pedantic -g3 -c $(SRC_MAIN) -I.

asm_obj:
	nasm -f elf64 -o 0-strlen.o 0-strlen.asm
	nasm -f elf64 $(SRC_ASM)

run: all
	$(EXE)
	rm -f $(EXE)

.PHONY: clean

clean:
	rm -f *.o $(EXE)