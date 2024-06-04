# Define the compiler and the compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Define the targets
TARGETS = add2PB findPhone

# Define the object files
OBJS = add2PB.o findPhone.o

# Default target
all: $(TARGETS)

# Target to compile add2PB
add2PB: add2PB.o
	$(CXX) $(CXXFLAGS) -o add2PB add2PB.o

# Target to compile findPhone
findPhone: findPhone.o
	$(CXX) $(CXXFLAGS) -o findPhone findPhone.o

# Rule to compile add2PB.o
add2PB.o: add2PB.cpp
	$(CXX) $(CXXFLAGS) -c add2PB.cpp

# Rule to compile findPhone.o
findPhone.o: findPhone.cpp
	$(CXX) $(CXXFLAGS) -c findPhone.cpp

# Clean target to remove compiled files
clean:
	rm -f $(OBJS) $(TARGETS)

# Run target to execute both programs with user input
add: all
	@echo "Enter Name:"
	@read NAME; \
	echo "Enter Last Name:"; \
	read LAST_NAME; \
	echo "Enter Phone Number:"; \
	read PHONE_NUMBER; \
	./add2PB "$$NAME" "$$LAST_NAME" "$$PHONE_NUMBER"; \
	echo "Enter the name to find the phone number:"; \
	read FIND_NAME; \
	./findPhone "$$FIND_NAME"

# Find target to execute the findPhone program
find: all
	@echo "Enter name to find the phone number:"
	@read FIND_NAME; \
	./findPhone "$$FIND_NAME"

.PHONY: all clean run find
