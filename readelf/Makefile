CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXE = 0-hreadelf

0-hreadelf: *.c
	$(CC) $(CFLAGS) *.c -o $(EXE)

run:
	./$(EXE)
	
.PHONY: clean
clean:
	rm -f ./$(EXE)
