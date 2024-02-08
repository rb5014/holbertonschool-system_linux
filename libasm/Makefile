

main_obj:
	@gcc -Wall -Wextra -Werror -pedantic -g3 -c tests/2-main.c -o tests/2-main.o -I.

asm_obj:
	@nasm -f elf64 -o tests/2-strncmp.o 2-strncmp.asm

all: main_obj asm_obj
	@gcc tests/2-main.o tests/2-strncmp.o -o 2-strncmp
	@make clean

2-strncmp: all
	./2-strncmp
	@rm -f ./2-strncmp

.PHONY: clean 2-strncmp

clean:
	rm -f tests/*.o