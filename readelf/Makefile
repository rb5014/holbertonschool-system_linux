CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
SRC_DIR0 = ./read_file_header
SRC_DIR1 = ./read_sections_headers
SRC_DIR2 = ./read_program_headers
EXE0 = 0-hreadelf
EXE1 = 1-hreadelf
EXE2 = 2-hreadelf
TEST0 = ./tests/test_file_header.sh
TEST1 = ./tests/test_sections_headers.sh
TEST2 = ./tests/test_program_headers.sh

0-hreadelf: $(SRC_DIR0)/*.c
	$(CC) $(CFLAGS) $(SRC_DIR0)/*.c -o $(EXE0)

0-hreadelf-no-w: $(SRC_DIR0)/*.c
	$(CC) $(SRC_DIR0)/*.c -o $(EXE0) -g

1-hreadelf: $(SRC_DIR1)/*.c
	$(CC) $(CFLAGS) $(SRC_DIR1)/*.c -o $(EXE1)

1-hreadelf-no-w: $(SRC_DIR1)/*.c
	$(CC) $(SRC_DIR1)/*.c -o $(EXE1) -g

2-hreadelf: $(SRC_DIR2)/*.c
	$(CC) $(CFLAGS) $(SRC_DIR2)/*.c -o $(EXE2)

2-hreadelf-no-w: $(SRC_DIR2)/*.c
	$(CC) $(SRC_DIR2)/*.c -o $(EXE2) -g

tests-file-header:
	$(TEST0)

tests-sections-headers:
	$(TEST1)

tests-program-headers:
	$(TEST2)
	
.PHONY: clean tests-file-header test-sections-headers test-program-headers
clean:
	rm -f ./$(EXE)
