CC = g++
Flags = -Wall -g -Wextra -DDEBUG

all: file1 file2 file3

file1: divideInZero.cpp
	ulimit -c unlimited && $(CC) $(Flags) -o file1 divideInZero.cpp

file2: infinityRecursion.cpp
	ulimit -c unlimited && $(CC) $(Flags) -o file2 infinityRecursion.cpp

file3: nullPointer.cpp
	ulimit -c unlimited && $(CC) $(Flags) -o file3 nullPointer.cpp

.PHONY: run1 run2 run3 debug1 debug2 debug3 clean

run1: file1
	./file1

run2: file2
	./file2

run3: file3
	./file3

debug1: file1
	ulimit -c unlimited && ddd ./file1 &

debug2: file2
	ulimit -c unlimited && ddd ./file2 &

debug3: file3
	ulimit -c unlimited && ddd ./file3 &

clean:
	rm -f file1 file2 file3 core

# To run: make all
# it automaticly open space for cores to dumps
#then for each one run it to dump core then debug it
# then it will open the graphic dbugger
#for gdb:
#after core dumped run "gdb file1 /mnt/wslg/dumps/core.file1.391259"
#						"gdb file2 /mnt/wslg/dumps/core.file2.392675"
#						"gdb file3 /mnt/wslg/dumps/core.file3.392845
# then run "list" to show the code or where to find where it crashed
#
#where: Shows the stack trace, indicating where the crash occurred.
#Use n (next) to execute the next line of code.
#Use s (step) to step into functions.
#Use c (continue) to continue executing until the next breakpoint or crash.