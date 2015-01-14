# Build Configuration
PLATFORM = $(shell uname -s)
SOURCE = ../../chlorine
TARGET = mandelbrot

# Set Compiler Flags
CCFLAGS := -O3 -std=c++11
CCFLAGS += -Wall -Wextra -Wpedantic
CCFLAGS += -Wno-unused-parameter

# Determine Correct Linking Flag
UNAME = $(shell uname -s)
ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenCL
else ifeq ($(UNAME), Linux)
LDFLAGS = -lOpenCL
endif

# Define Makefile Aliases
default: clean $(TARGET)
all: default
clean:
	@rm -rf *.gcda *.gcno *.gcov
	@rm -rf *.ppm
	@rm -rf $(TARGET)
.PHONY: $(TARGET)

# Build the Example Target
$(TARGET): $(TARGET).cpp
	$(CXX) $(CCFLAGS) -I$(SOURCE) $< -o $@ $(LDFLAGS)
