# Pre-compiler and Compiler flags
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb
PRE_FLAGS := -MMD -MP

# Project directory structure
BIN := bin
SRC := src
LIB := lib
INC := include
MAINFILE := $(SRC)/main.cpp

# Build directories and output
TARGET := $(BIN)/main
BUILD := build

# Library search directories and flags

OPENCVINCLUDE = `pkg-config opencv4 --cflags`
OPENCVINCLIB = `pkg-config opencv4 --libs`
ARMADILLOLIB = -llapack -lblas -larmadillo

EXT_LIB :=
LDFLAGS :=
LDPATHS := $(addprefix -L,$(LIB) $(EXT_LIB)) $(OPENCVINCLIB) $(ARMADILLOLIB)

# Include directories
INC_DIRS := $(INC) $(shell find $(SRC) -type d) 
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(OPENCVINCLUDE)

# Construct build output and dependency filenames
SRCS := $(shell find $(SRC) -name "*.cpp")
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))
DEPS := $(OBJS:.o=.d)

# Run task
run: build
	@echo "🚀 Executing..."
	./$(TARGET) $(ARGS)

# Build task
build: all

# Main task
all: $(TARGET)

# Task producing target from built files
$(TARGET): $(OBJS)
	@echo "🚧 Building..."
	mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDPATHS) $(LDFLAGS)

# Compile all cpp files
$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(PRE_FLAGS) $(INC_FLAGS) -c -o $@ $< $(LDPATHS) $(LDFLAGS)

# Clean task
.PHONY: clean
clean:
	@echo "🧹 Clearing..."
	rm -rf build

# Include all dependencies
-include $(DEPS)
