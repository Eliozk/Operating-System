CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target executable
TARGET = main

# Source files
SRC = getFromstd.cpp

# Default make target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean target
clean:
	rm -f $(TARGET)

#what to write to terminal
#./main < input.txt
