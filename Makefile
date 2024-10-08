# Compiler
CC := clang

# Compiler flags
CFLAGS := -Wall -Wextra -std=c2x -O2 -MMD

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TESTS_DIR := tests
TESTS_OBJ_DIR := $(OBJ_DIR)/tests

# Target executable
TARGET := $(BIN_DIR)/app
TEST_TARGET := $(BIN_DIR)/test_args

# Source files
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
TEST_SRCS := $(shell find $(TESTS_DIR) -type f -name '*.c')

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS := $(patsubst $(TESTS_DIR)/%.c,$(TESTS_OBJ_DIR)/%.o,$(TEST_SRCS))

# Include paths
INCLUDES := -I$(SRC_DIR)

# Libraries
LIBS := 
TEST_LIBS := -lcheck

# Default target
all: $(TARGET)

# Build application
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $@ $^

# Run application with arguments
.PHONY: run
run: $(TARGET)
	@$(TARGET) $(ARGS)

# Build tests
tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $@ $^ $(TEST_LIBS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Compile test files
$(TESTS_OBJ_DIR)/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Run tests
run_tests: tests
	@$(BIN_DIR)/test_args

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include dependency files
-include $(OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)

.PHONY: all clean tests run_tests

