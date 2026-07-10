# NOTE: For this makefile to work correctly, all .cpp files present
#       in $(SRC_PATH) and its subfolders must have their corresponding
#       .hpp files in the $(INC_PATH) folder.

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
$(filter-out $3,$(wildcard $1/*.$2)) \
$(foreach dir,$(wildcard $1/*),$(call find_files_in_subdirs,$(dir),$2,$3))
endef

# ============================================================================
# Directories
# ============================================================================

BUILD_PATH = ./build

RELEASE_PATH = $(BUILD_PATH)/release
DEBUG_PATH = $(BUILD_PATH)/debug
TEST_BUILD_PATH = $(BUILD_PATH)/tests

RELEASE_OBJ_PATH = $(RELEASE_PATH)/obj
DEBUG_OBJ_PATH = $(DEBUG_PATH)/obj
TEST_OBJ_PATH = $(TEST_BUILD_PATH)/obj

INC_PATH = ./inc
SRC_PATH = ./src
TEST_PATH = ./test
DOCTEST_PATH = ./third-party/doctest

INC_SUBPATHS = $(INC_PATH)/ $(call find_subdirs,$(INC_PATH))

TEST_INC_SUBPATHS = \
	$(DOCTEST_PATH)/ \
	$(call find_subdirs,$(TEST_PATH))

# ============================================================================
# Flex / Bison
# ============================================================================

BISON = bison
FLEX = flex

BISON_SRC = $(SRC_PATH)/parser.y
FLEX_SRC = $(SRC_PATH)/lexer.l

LEX_YACC_OUTPUT = $(BUILD_PATH)/lex-yacc-generated

BISON_OUTPUT_C = $(LEX_YACC_OUTPUT)/parser.tab.c
BISON_OUTPUT_H = $(LEX_YACC_OUTPUT)/parser.tab.h

FLEX_OUTPUT = $(LEX_YACC_OUTPUT)/lex.yy.c

# ============================================================================
# Compiler
# ============================================================================

CXX = g++

COMMON_FLAGS = -Wall -Wextra -std=c++17

RELEASE_FLAGS = $(COMMON_FLAGS)
DEBUG_FLAGS = $(COMMON_FLAGS) -g -O0

INC_FLAGS := \
	$(addprefix -I,$(INC_SUBPATHS)) \
	-I $(LEX_YACC_OUTPUT)

TEST_INC_FLAGS := \
	$(addprefix -I,$(INC_SUBPATHS)) \
	$(addprefix -I,$(TEST_INC_SUBPATHS))

# ============================================================================
# Source files
# ============================================================================

MAIN_FILE := $(SRC_PATH)/main.cpp

SRC_FILES := $(call find_files_in_subdirs,$(SRC_PATH),cpp,$(MAIN_FILE))

TEST_MAIN = $(TEST_PATH)/main.cpp

TEST_FILES := \
$(call find_files_in_subdirs,$(TEST_PATH),cpp,$(TEST_MAIN))

RELEASE_OBJ_FILES := \
$(patsubst $(SRC_PATH)/%.cpp,$(RELEASE_OBJ_PATH)/%.o,$(SRC_FILES))

DEBUG_OBJ_FILES := \
$(patsubst $(SRC_PATH)/%.cpp,$(DEBUG_OBJ_PATH)/%.o,$(SRC_FILES))

TEST_OBJ_FILES := \
$(patsubst $(TEST_PATH)/%.cpp,$(TEST_OBJ_PATH)/%.o,$(TEST_FILES))

# ============================================================================
# Targets
# ============================================================================

RELEASE_TARGET = $(RELEASE_PATH)/tsed
DEBUG_TARGET = $(DEBUG_PATH)/tsed
TEST_TARGET = $(TEST_BUILD_PATH)/tests

# ============================================================================
# Main rules
# ============================================================================

all: release

release: $(RELEASE_TARGET)

debug: $(DEBUG_TARGET)

test: $(BISON_OUTPUT_C) $(FLEX_OUTPUT) $(RELEASE_OBJ_FILES) $(TEST_TARGET)
	$(TEST_TARGET)

# ============================================================================
# Link rules
# ============================================================================

$(RELEASE_TARGET): $(BISON_OUTPUT_C) $(FLEX_OUTPUT) $(RELEASE_OBJ_FILES) $(MAIN_FILE)
	@mkdir -p $(dir $@)
	$(CXX) $(RELEASE_FLAGS) $(INC_FLAGS) $^ -o $@

$(DEBUG_TARGET): $(BISON_OUTPUT_C) $(FLEX_OUTPUT) $(DEBUG_OBJ_FILES) $(MAIN_FILE)
	@mkdir -p $(dir $@)
	$(CXX) $(DEBUG_FLAGS) $(INC_FLAGS) $^ -o $@

$(TEST_TARGET): $(BISON_OUTPUT_C) $(FLEX_OUTPUT) $(RELEASE_OBJ_FILES) $(TEST_OBJ_FILES) $(TEST_MAIN)
	@mkdir -p $(dir $@)
	$(CXX) $(RELEASE_FLAGS) $(TEST_INC_FLAGS) $^ -o $@

# ============================================================================
# Bison rules
# ============================================================================

$(BISON_OUTPUT_C) $(BISON_OUTPUT_H): $(BISON_SRC)
	@mkdir -p $(dir $(BISON_OUTPUT_C))
	$(BISON) -d -o $(BISON_OUTPUT_C) $(BISON_SRC)

# ============================================================================
# Flex rules
# ============================================================================

$(FLEX_OUTPUT): $(FLEX_SRC)
	@mkdir -p $(dir $@)
	$(FLEX) -o $@ $(FLEX_SRC)

# ============================================================================
# Object compilation rules
# ============================================================================

$(RELEASE_OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC_PATH)/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) $(RELEASE_FLAGS) $(INC_FLAGS) -c $< -o $@

$(DEBUG_OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC_PATH)/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) $(DEBUG_FLAGS) $(INC_FLAGS) -c $< -o $@

$(TEST_OBJ_PATH)/%.o: $(TEST_PATH)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(RELEASE_FLAGS) $(TEST_INC_FLAGS) -c $< -o $@

# ============================================================================
# Clean rules
# ============================================================================

clean:
	rm -rf $(BUILD_PATH)

clean-release:
	rm -rf $(RELEASE_PATH)

clean-debug:
	rm -rf $(DEBUG_PATH)

clean-test:
	rm -rf $(TEST_BUILD_PATH)

# ============================================================================
# Phony targets
# ============================================================================

.PHONY: \
	all \
	release \
	debug \
	test \
	clean \
	clean-release \
	clean-debug \
	clean-test
