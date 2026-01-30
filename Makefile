# Compiler
CXX := g++
CC  := clang

# Paths
SRC_DIR   := .
GEN_DIR   :=
BUILD_DIR := build

TARGET := $(BUILD_DIR)/main

INCLUDES := \
	-I$(SRC_DIR) \
	-I$(GEN_DIR)

INCLUDES += $(shell pkg-config libc)

# Compiler flags (C only)
CFLAGS := \
					-g \
					-o0



# Compiler flags (C++ only)
CXXFLAGS :=

# Linker flags
LDFLAGS :=

# Sources (unity build)
SOURCES := \
	main.c

# Quiet / verbose toggle
ifndef VERBOSE
Q := @
endif

# Rules
all: $(TARGET)

run: $(TARGET)
	$(Q)./$(TARGET)

$(TARGET): $(SOURCES)
	$(Q)mkdir -p $(BUILD_DIR)
	$(Q)$(CC) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	$(Q)rm -rf $(BUILD_DIR)

.PHONY: all run clean
