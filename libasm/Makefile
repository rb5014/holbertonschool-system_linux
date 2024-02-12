
all: main_obj asm_obj
	@gcc tests/5-main.o tests/5-memcpy.o -o 5-memcpy
	@make clean

main_obj:
	@gcc -Wall -Wextra -pedantic -g3 -c tests/5-main.c -o tests/5-main.o -I.

asm_obj:
	@nasm -f elf64 -o tests/5-memcpy.o 5-memcpy.asm

5-memcpy: all
	./5-memcpy
	@rm -f ./5-memcpy

.PHONY: clean 5-memcpy

clean:
	rm -f tests/*.o