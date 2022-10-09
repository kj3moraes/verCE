# Compiler and Linker
CXX				:= clang++

# Target executable(s)
TARGET_PRM		:= verCEPrompt
TARGET_PRG		:= verCEProgram

# Main for the two variants
MAIN_PRM 		:= MainPrompt.cc
MAIN_PRG 		:= MainProgram.cc

# Directories
SRC_DIR			:= src
OBJ_DIR			:= build
INCLUDE_DIR		:= include
TARGET_DIR		:= bin
RES_DIR			:= resources

# Extensions
SRC_EXT			:= cc
DEP_EXT 		:= d
OBJ_EXT			:= o

# Flags and Libraries
CXX_FLAGS 		:= -std=c++14 -Wall -Wextra -Wpedantic -g -O0
LIB_FLAGS 		:= -lm -lLLVM-13
LLVM_LIB_SPEC	:= `llvm-config --cxxflags --ldflags --system-libs --libs core`
INC_FLAGS 		:= -I$(INCLUDE_DIR) -I/usr/local/include -I.
INC_DEP			:= -I$(INCLUDE_DIR)

# ---------------------------------------------------------------------------------------
# Do not edit below this line
# ---------------------------------------------------------------------------------------

# =================================== COMMON FUNCS ======================================

# Default Make
all: directories $(TARGET_PRM) # $(TARGET_PRM)

# Remake the executable
remake: purge all

# Make the directories
directories:
	mkdir -p $(TARGET_DIR)
	mkdir -p $(OBJ_DIR)

# Clean only Objects
clean:
	@$(RM) -rf $(OBJ_DIR)

# Full Clean, Objects and Binaries
purge: clean
	@$(RM) -rf $(TARGET_DIR)


# =================================== TEST PROMPT =======================================

SOURCES_PRM     := $(shell find $(SRC_DIR) -type f ! -name $(MAIN_PRG) -name *.$(SRC_EXT))
OBJECTS_PRM     := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES_PRM:.$(SRC_EXT)=.$(OBJ_EXT)))

# Pull in dependency info for existing .o files
-include $(OBJECTS_PRM:.$(OBJ_EXT)=.$(DEP_EXT))

# Link
$(TARGET_PRM): $(OBJECTS_PRM)
	$(CXX) -o $(TARGET_DIR)/$(TARGET_PRM) $^ $(LIB_FLAGS)

# =======================================================================================


# ================================== TEST PROGRAM =======================================

SOURCES_PRG     := $(shell find $(SRC_DIR) -type f ! -name $(MAIN_PRM) -name *.$(SRC_EXT))
OBJECTS_PRG     := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES_PRG:.$(SRC_EXT)=.$(OBJ_EXT)))

# Pull in dependency info for existing .o files
-include $(OBJECTS_PRG:.$(OBJ_EXT)=.$(DEP_EXT))

# Link
$(TARGET_PRG): $(OBJECTS_PRG)
	$(CXX) -o $(TARGET_DIR)/$(TARGET_PRG) $^ $(LIB_FLAGS)

# =======================================================================================

# Compile
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(LLVM_LIB_SPEC	) $(INC_FLAGS) -c -o $@ $<
	@$(CXX) $(CXX_FLAGS) $(INC_DEP) -MM $(SRC_DIR)/$*.$(SRC_EXT) > $(OBJ_DIR)/$*.$(DEP_EXT)
	@cp -f $(OBJ_DIR)/$*.$(DEP_EXT) $(OBJ_DIR)/$*.$(DEP_EXT).tmp
	@sed -e 's|.*:|$(OBJ_DIR)/$*.$(OBJ_EXT):|' < $(OBJ_DIR)/$*.$(DEP_EXT).tmp > $(OBJ_DIR)/$*.$(DEP_EXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJ_DIR)/$*.$(DEP_EXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJ_DIR)/$*.$(DEP_EXT)
	@rm -f $(OBJ_DIR)/$*.$(DEP_EXT).tmp


# Non-File Targets
.PHONY: all remake clean purge directories