CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXE = 0-hreadelf

0-hreadelf: *.c
	$(CC) $(CFLAGS) *.c -o $(EXE)

0-hreadelf_no_w: *.c
	$(CC) *.c -o $(EXE) -g


tests:
	./tests/test1.sh
	
.PHONY: clean tests
clean:
	rm -f ./$(EXE)
