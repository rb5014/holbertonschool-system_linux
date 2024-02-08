

main_obj:
	@gcc -Wall -Wextra -Werror -pedantic -g3 -c tests/3-main.c -o tests/3-main.o -I.

asm_obj:
	@nasm -f elf64 -o tests/3-strchr.o 3-strchr.asm

all: main_obj asm_obj
	@gcc tests/3-main.o tests/3-strchr.o -o 3-strchr
	@make clean

3-strchr: all
	./3-strchr
	@rm -f ./3-strchr

.PHONY: clean 3-strchr

clean:
	rm -f tests/*.o