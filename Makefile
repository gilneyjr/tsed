# NOTE: toFor this makefile to work correctly, all .cpp files present 
#       in $(SRC_PATH) and its subfolders must have their corresponding 
#       files in the $(INC_PATH) folder.

# Function to find all subdirectories of a given directory.
# $1 is the target directory.
define find_subdirs
$(wildcard $1/*/) $(foreach dir,$(wildcard $1/*),$(call find_subdirs,$(dir)))
endef

# Function to find all files in subdirectories of a given directory.
# $1 is the target directory.
# $2 is the extension that the found files should have.
# $3 is the file name to be excluded from the results.
define find_files_in_subdirs
$(filter-out $3, $(wildcard $1/*.$2)) $(foreach dir,$(wildcard $1/*),$(call find_files_in_subdirs,$(dir),$2,$3))
endef

# Directories
BUILD_PATH = ./build
OBJ_PATH = $(BUILD_PATH)/obj
INC_PATH = ./inc
INC_SUBPATHS = $(INC_PATH)/ $(call find_subdirs,$(INC_PATH))
SRC_PATH = ./src

# Name of the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17
INC_FLAGS := $(addprefix -I, $(INC_SUBPATHS))

# Bison and Flex tools
BISON = bison
FLEX = flex

# Source file names
BISON_SRC = $(SRC_PATH)/parser.y
FLEX_SRC = $(SRC_PATH)/lexer.l

# TODO: ver uma forma de excluir o main.cpp depois e retirar do find_files_in_subdirs
MAIN_FILE := $(SRC_PATH)/main.cpp

# Generated files
LEX_YACC_OUTPUT = $(BUILD_PATH)/lex-yacc-generated
BISON_OUTPUT_C = $(LEX_YACC_OUTPUT)/parser.tab.c
BISON_OUTPUT_H = $(LEX_YACC_OUTPUT)/parser.tab.h
FLEX_OUTPUT = $(LEX_YACC_OUTPUT)/lex.yy.c
SRC_FILES := $(call find_files_in_subdirs,$(SRC_PATH),cpp,$(MAIN_FILE))
OBJ_FILES := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SRC_FILES))

# Name of the executable
TARGET = $(BUILD_PATH)/tsed

# Default rule: builds everything
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(BISON_OUTPUT_C) $(FLEX_OUTPUT) $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) $(BISON_OUTPUT_C) $(FLEX_OUTPUT) $(OBJ_FILES) -o $@

# Rule to generate parser.tab.c and parser.tab.h from the Bison file
$(BISON_OUTPUT_C) $(BISON_OUTPUT_H): $(BISON_SRC)
	@mkdir -p $(dir $(BISON_OUTPUT_C))
	$(BISON) -d -o $(BISON_OUTPUT_C) $(BISON_SRC)

# Rule to generate lex.yy.c from the Flex file
$(FLEX_OUTPUT): $(FLEX_SRC)
	@mkdir -p $(dir $@)
	$(FLEX) -o $@ $(FLEX_SRC)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC_PATH)/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

# Cleans up generated files
clean:
	rm -rf $(BUILD_PATH)

.PHONY: all clean
