# Compiler and flags -pg for gprof

CXX = g++
CXXFLAGS = -Wall -O2 -pg

# Target for building all
all: main

# Target for building the main executable
main: main.o timeN.o timeN2.o timeN3.o
	$(CXX) $(CXXFLAGS) -o main main.o timeN.o timeN2.o timeN3.o

# Target for compiling main.cpp
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Target for compiling timeN.cpp
timeN.o: timeN.cpp
	$(CXX) $(CXXFLAGS) -c timeN.cpp

# Target for compiling timeN2.cpp
timeN2.o: timeN2.cpp
	$(CXX) $(CXXFLAGS) -c timeN2.cpp

# Target for compiling timeN3.cpp
timeN3.o: timeN3.cpp
	$(CXX) $(CXXFLAGS) -c timeN3.cpp

# Target for running the main program
run: all
	@echo "Running main...\n"
	@./main 

# Target for profiling the main program
profile: all
	@echo "Profiling main...\n"
	@./main 
	@gprof main gmon.out > profile.txt

# Target for cleaning object files and executables
clean:
	rm -f *.o main profile.txt gmon.out

# Phony targets (targets that are not actual files)
.PHONY: all run profile clean
