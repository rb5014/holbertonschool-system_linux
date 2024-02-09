

main_obj:
	@gcc -Wall -Wextra -pedantic -g3 -c tests/4-main.c -o tests/4-main.o -I.

asm_obj:
	@nasm -f elf64 -o tests/4-strstr.o 4-strstr.asm

all: main_obj asm_obj
	@gcc tests/4-main.o tests/4-strstr.o -o 4-strstr
	@make clean

4-strstr: all
	./4-strstr
	@rm -f ./4-strstr

.PHONY: clean 4-strstr

clean:
	rm -f tests/*.o