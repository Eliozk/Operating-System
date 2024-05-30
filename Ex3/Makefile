# Define the C++ compiler to use
CXX = clang++

# Define the compilation flags
# -std=c++11: Use the C++11 standard
# -Wall: Enable all warnings
CXXFLAGS = -std=c++11 -Wall

# Define the linker flags
# -lm: Link with the math library
LDFLAGS = -lm

# Define the target executable name
TARGET = poisson

# Define the source file
SRC = main.cpp

# Define the path to the shared library
LIB = /home/elioz/Operating\ Systems/Ex2/libpoisson.so

# Default rule to build the target
all: $(TARGET)


# $(LDFLAGS): The linker flags
$(TARGET): $(SRC) $(LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -L/home/elioz/Operating\ Systems/Ex2 -l:libpoisson.so $(LDFLAGS)

# Rule to run the program
# LD_LIBRARY_PATH: Specify the library path for runtime
run: $(TARGET)
	LD_LIBRARY_PATH=/home/elioz/Operating\ Systems/Ex2 ./$(TARGET)

# Rule to clean up generated files
clean:
	rm -f $(TARGET)

# Declare these rules as not actual files
.PHONY: all run clean
