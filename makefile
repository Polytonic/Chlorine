# Build Configuration
PLATFORM = $(shell uname -s)
SOURCE = chlorine
OUTPUT = builds

# Set Test Configuration
TEST_DIR = tests
TEST_LIB = $(TEST_DIR)/googletest/include/
TESTSUITE = \
	vectors	\

# Set Compiler Flags
CCFLAGS := -O3 -std=c++11
CCFLAGS += -Wall -Wextra -Wpedantic
CCFLAGS += -Wno-unused-parameter

# Enable Code Coverage
ifeq ($(TRAVIS), true)
CCFLAGS += -fprofile-arcs -ftest-coverage
endif

# Determine Correct Linking Flag
UNAME = $(shell uname -s)
ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenCL
else ifeq ($(UNAME), Linux)
LDFLAGS = -lOpenCL
endif

# Define Makefile Aliases
default: clean chlorine clinfo
all: default $(TESTSUITE)
clean:
	@rm -rf *.gcda *.gcno *.gcov
	@rm -rf $(OUTPUT)
	@rm -rf $(TEST_DIR)/$(OUTPUT)
.PHONY: chlorine

# Build the Chlorine CLI Executable
chlorine: $(SOURCE)/chlorine.cpp
	@mkdir -p $(OUTPUT)
	$(CXX) $(CCFLAGS) $< -o $(OUTPUT)/$@ $(LDFLAGS)

# Build the clinfo Diagnostic Utility
clinfo: $(SOURCE)/clinfo.cpp
	@mkdir -p $(OUTPUT)
	$(CXX) $(CCFLAGS) $< -o $(OUTPUT)/$@ $(LDFLAGS)

%: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_DIR)/$(OUTPUT)
	$(CXX) $(CCFLAGS) -I$(SOURCE) -I$(TEST_LIB) $< -o $(TEST_DIR)/$(OUTPUT)/$@ $(LDFLAGS)

test:
	./$(OUTPUT)/chlorine
	./$(TEST_DIR)/$(OUTPUT)/vectors
