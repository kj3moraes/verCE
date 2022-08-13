# ==========================================================
#  					MAKEFILE for verCE
# ==========================================================

# Compiler and Linker
CXX				:= clang

# Flags and Libraries
CXX_FLAGS 		:= -Wall -Wextra -Wpedantic -g -O3 
LIB_FLAGS 		:= `llvm-config --cxxflags --ldflags --system-libs --ldflags --libs core`
INC_FLAGS 		:= -I/usr/local/include -I. 
INC_DEP			:= -I$(INCLUDE_DIR)

# Target executable
TARGET			:= verCE

# Directories
SRC_DIR			:= src
OBJ_DIR			:= build
INCLUDE_DIR		:= include
TARGET_DIR		:= bin
RES_DIR			:= res

# Extensions
SRC_EXT			:= cc
DEP_EXT 		:= d
OBJ_EXT			:= o

# ------------------------------------------------------------------------------
# Do not edit below this line
# ------------------------------------------------------------------------------

SOURCES     := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS     := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.$(SRC_EXT)=.$(OBJ_EXT)))

# Default Make
all: directories resources $(TARGET)

# Remake the executable
remake: purge all

# Make the directories
directories:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(OBJ_DIR)

# Clean only Objects
clean:
	@$(RM) -rf $(OBJ_DIR) 
	

# Full Clean : objects, dependencies and directories
purge: clean
	@$(RM) -rf $(TARGET_DIR)
	@$(RM) -d $(TARGET_DIR) $(OBJ_DIR)

# Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJ_EXT)=.$(DEP_EXT))

# Link
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET_DIR)/$(TARGET) $^ $(LIB_FLAGS)

# Compile
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c -o $@ $<
	@$(CXX) $(CXX_FLAGS) $(INC_DEP) -MM $(SRC_DIR)/$*.$(SRC_EXT) > $(OBJ_DIR)/$*.$(DEP_EXT)
	@cp -f $(OBJ_DIR)/$*.$(DEP_EXT) $(OBJ_DIR)/$*.$(DEP_EXT).tmp
	@sed -e 's|.*:|$(OBJ_DIR)/$*.$(OBJ_EXT):|' < $(OBJ_DIR)/$*.$(DEP_EXT).tmp > $(OBJ_DIR)/$*.$(DEP_EXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJ_DIR)/$*.$(DEP_EXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJ_DIR)/$*.$(DEP_EXT)
	@rm -f $(OBJ_DIR)/$*.$(DEP_EXT).tmp

# Non-File Targets
.PHONY: all remake clean purge resources