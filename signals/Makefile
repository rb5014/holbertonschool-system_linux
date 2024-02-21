# Define the rule for compiling with the specified source file
%: %.c
	gcc -Wall -Wextra -Werror -pedantic main.c 1-set_print_hello.c $<
	./a.out
	rm -f ./a.out

	
