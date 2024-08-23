# Directories
BUILD_PATH = ./build
OBJ_PATH = $(BUILD_PATH)/obj
INC_PATH = ./inc
SRC_PATH = ./src

# Name of the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Bison and Flex tools
BISON = bison
FLEX = flex

# Source file names
BISON_SRC = $(SRC_PATH)/parser.y
FLEX_SRC = $(SRC_PATH)/lexer.l

# Generated files
LEX_YACC_OUTPUT = $(BUILD_PATH)/lex-yacc-generated
BISON_OUTPUT_C = $(LEX_YACC_OUTPUT)/parser.tab.c
BISON_OUTPUT_H = $(LEX_YACC_OUTPUT)/parser.tab.h
FLEX_OUTPUT = $(LEX_YACC_OUTPUT)/lex.yy.c

# Name of the executable
TARGET = $(BUILD_PATH)/tsed

# Default rule: builds everything
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(BISON_OUTPUT_C) $(FLEX_OUTPUT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $(BISON_OUTPUT_C) $(FLEX_OUTPUT)

# Rule to generate parser.tab.c and parser.tab.h from the Bison file
$(BISON_OUTPUT_C) $(BISON_OUTPUT_H): $(BISON_SRC)
	@mkdir -p $(dir $(BISON_OUTPUT_C))
	$(BISON) -d -o $(BISON_OUTPUT_C) $(BISON_SRC)

# Rule to generate lex.yy.c from the Flex file
$(FLEX_OUTPUT): $(FLEX_SRC)
	@mkdir -p $(dir $@)
	$(FLEX) -o $@ $(FLEX_SRC)

# Cleans up generated files
clean:
	rm -rf $(BUILD_PATH)

.PHONY: all clean
