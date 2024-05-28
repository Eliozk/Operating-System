CC = clang++
CFLAGS = -Wall -Wextra -std=c++11 -g --coverage
OBJ_DIR = objectFiles
TARGET = main_infinityRecursion main_divideInZero main_nullPointer

all: $(addprefix $(OBJ_DIR)/,$(TARGET))

$(OBJ_DIR)/main_%: $(OBJ_DIR)/%.o | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run1: $(OBJ_DIR)/main_infinityRecursion
	./$<

run2: $(OBJ_DIR)/main_divideInZero
	./$<

run3: $(OBJ_DIR)/main_nullPointer
	./$<

core: core_infinityRecursion core_divideInZero core_nullPointer

core_%: $(OBJ_DIR)/main_%
	ulimit -c unlimited && ./$<

debug_core: core
	gdb $(OBJ_DIR)/main_$(PROGRAM) core

coverage: all
	./$(TARGET)
	gcov $(addsuffix .cpp,$(TARGET))

clean:
	rm -rf $(OBJ_DIR) *.gcov *.gcda *.gcno $(TARGET) core

.PHONY: all clean run1 run2 run3 core debug_core coverage
