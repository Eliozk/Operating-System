CC = g++
Flags = -Wall -g -Wextra

all: file1 file2 file3

file1: divideInZero.cpp
	$(CC) $(Flags) -o file1 divideInZero.cpp

file2: infinityRecursion.cpp
	$(CC) $(Flags) -o file2 infinityRecursion.cpp

file3: nullPointer.cpp
	$(CC) $(Flags) -o file3 nullPointer.cpp

.PHONY: run1 run2 run3 debug1 debug2 debug3 clean all
run1: file1
	./file1

run2: file2
	./file2

run3: file3
	./file3


debug1: file1 
	ddd ./file1 &
debug2: file2 
	ddd ./file2 &
debug3:
	ddd ./file3 &

clean:
	rm -f file1 file2 file3
