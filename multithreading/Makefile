0-thread_entry: clean
	gcc -Wall -Wextra -Werror -pedantic -g3 0-main.c 0-thread_entry.c -o 0-thread_entry -pthread

1-tprintf: clean
	gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c 1-tprintf.c -o 1-tprintf -pthread

10-blur_portion.c: clean
	gcc -g -Wall -Wextra -Werror -pedantic -g3 10-main.c 10-blur_portion.c -o 10-blur_portion

11-blur_image: clean
	gcc -Wall -Wextra -Werror -pedantic -g3 11-main.c 11-blur_image.c 10-blur_portion.c -o 11-blur_image -pthread

clean:
	rm -f 0-thread_entry 1-tprintf