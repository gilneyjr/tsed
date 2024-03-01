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
BIN_PATH = ./bin
INC_PATH = ./inc
INC_SUBPATHS = $(INC_PATH)/ $(call find_subdirs,$(INC_PATH))
OBJ_PATH = ./obj
SRC_PATH = ./src

# Files
MAIN_FILE := $(SRC_PATH)/main.cpp
TARGET_FILE := $(BIN_PATH)/tsed
SRC_FILES := $(call find_files_in_subdirs,$(SRC_PATH),cpp,$(MAIN_FILE))
OBJ_FILES := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SRC_FILES))

# Compiler and flags
CXX = g++
CXX_FLAGS = -std=c++17 -Wall
INC_FLAGS := $(addprefix -I, $(INC_SUBPATHS))

$(TARGET_FILE): $(OBJ_FILES) $(MAIN_FILE)
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) $(MAIN_FILE) $(OBJ_FILES) -o $(TARGET_FILE)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC_PATH)/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c $< -o $@

run: $(TARGET_FILE)
	@$(TARGET_FILE)

clean:
	rm -rf $(BIN_PATH) $(OBJ_PATH)

.PHONY: run clean











# Function to find all subdirectories from a folder
# define find_subdirs
# $(wildcard $1/*/) $(foreach dir,$(wildcard $1/*),$(call find_subdirs,$(dir)))
# endef

# define find_files_ind_subdirs_by_extension
# $(wildcard $1/*/) $(foreach dir,$(wildcard $1/*),$(call find_subdirs,$(dir)))
# endef

# # Diretórios
# INCLUDE_DIR = include
# INCLUDE_SUBDIRS := $(INCLUDE_DIR)/ $(call find_subdirs,$(INCLUDE_DIR))
# SRC_DIR = src
# BUILD_DIR = build
# TARGET = tsed

# # Compiler and options
# CXX = g++
# CXXFLAGS = -std=c++17 -Wall
# INCLUDE_FLAGS := $(addprefix -I, $(INCLUDE_SUBDIRS))

# # Source files and object files
# SOURCES := $(call find_files_ind_subdirs_by_extension,$(SRC_DIR), .cpp)
# #$(wildcard $(SRC_DIR)/**/*.cpp)
# OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# # Executable target
# $(TARGET): $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) $^ -o $@

# # Rule to compile objects
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# # Rule for objects compilation

# print:
# 	@echo $(SOURCES)

# # Rule to clean temporary files
# clean:
# 	rm -rf $(BUILD_DIR) $(TARGET)

# .PHONY: clean