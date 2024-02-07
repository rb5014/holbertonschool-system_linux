CC = gcc
NASM = nasm
CFLAGS = -Wall -Werror -Wextra -pedantic -g3

all: clean 0-strlen

0-strlen: 0-main.o 0-strlen.o
	$(CC) -o $@ $^

0-main.o: 0-main.c
	$(CC) $(CFLAGS) -c $< -o $@

0-strlen.o: 0-strlen.asm
	$(NASM) -f elf64 $< -o $@

clean:
	rm -f *.o 0-strlen
