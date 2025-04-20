CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

INCLUDE_DIR = include
SOURCE_DIR = source
TEST_DIR = test
OBJ_DIR = obj

SRC_FILES = $(filter-out $(SOURCE_DIR)/main.c, $(wildcard $(SOURCE_DIR)/*.c))
OBJ_FILES = $(patsubst $(SOURCE_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN_OBJ = $(OBJ_DIR)/main.o

TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC_FILES))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

# Build the tests - one executable per test file
tests: $(foreach file,$(TEST_SRC_FILES),$(basename $(notdir $(file))))

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Rule to build each test separately
%: $(OBJ_DIR)/%.o $(OBJ_FILES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET) $(foreach file,$(TEST_SRC_FILES),$(basename $(notdir $(file))))

.PHONY: all clean tests