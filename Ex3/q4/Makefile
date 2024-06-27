# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source file
SRCS = server_graph.cpp

# Executable name
EXEC = serverrun

# Default target
all: $(EXEC)

# Compile target
$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) -pthread

# Clean target
clean:
	rm -f $(EXEC)
