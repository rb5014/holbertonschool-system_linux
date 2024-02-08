

main_obj:
	@gcc -Wall -Wextra -Werror -pedantic -g3 -c tests/1-main.c -o tests/1-main.o -I.

asm_obj:
	@nasm -f elf64 -o tests/1-strcmp.o 1-strcmp.asm

all: main_obj asm_obj
	@gcc tests/1-main.o tests/1-strcmp.o -o 1-strcmp
	@make clean

1-strcmp: all
	./1-strcmp
	@rm -f ./1-strcmp

.PHONY: clean 1-strcmp

clean:
	rm -f tests/*.o