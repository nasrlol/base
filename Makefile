# Compiler
CXX := g++
CC  := clang

# Paths
SRC_DIR   := .
GEN_DIR   :=
BUILD_DIR := .
TARGET    := ./main

# Include paths
INCLUDES := -I$(SRC_DIR)
# Note: pkg-config libc is unusual - typically you wouldn't need this
# INCLUDES += $(shell pkg-config --cflags libc)

# Compiler flags (C only)
CFLAGS := -g

# Compiler flags (C++ only)
CXXFLAGS :=

# Linker flags
LDFLAGS :=

# Sources (unity build)
SOURCES := main.c

# Rules
.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(INCLUDES) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	$(TARGET)
