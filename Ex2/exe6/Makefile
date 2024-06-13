all: ttt mync

ttt:
	gcc -Wall -Wextra -std=c99 -o ttt ttt.c

mync:
	gcc -Wall -Wextra -std=c99 -fprofile-arcs -ftest-coverage -o mync mync.c
#after running the program to calc usage of the code
coverage: 
	gcov mync.c

clean:
	rm -f ttt mync *.gcov *.gcda *.gcno

.PHONY: all coverage clean
