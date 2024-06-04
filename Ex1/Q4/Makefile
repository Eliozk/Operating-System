# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -O2 -fprofile-arcs -ftest-coverage

# Target executable
TARGET = dijkstra

# Source files
SRCS = dijkstraAlgo.cpp 

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean build files
clean:
	rm -f $(TARGET) $(OBJS) *.gcno *.gcda *.gcov

# Rule to run gcov for code coverage on dijkstraAlgo.cpp
gcov: all
	./test.sh
	./$(TARGET)  # Run dijkstra manually after tests and coverage
	gcov $(SRCS)

# Rule to run the program
run: all
	./$(TARGET)

# Rule to run test cases using the shell script
test:
	./test.sh

.PHONY: all clean gcov run test
