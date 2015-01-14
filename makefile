# Build Configuration
PLATFORM = $(shell uname -s)
SOURCE = chlorine
OUTPUT = builds

# Set Test Configuration
TEST_DIR = tests
TEST_LIB = $(TEST_DIR)/catch/single_include/
TESTSUITE = test_main

# Set Compiler Flags
CCFLAGS := -O3 -std=c++11
CCFLAGS += -Wall -Wextra -Wpedantic
CCFLAGS += -Wno-unused-parameter

# Enable Code Coverage
ifeq ($(TRAVIS), true)
CIFLAGS := -fprofile-arcs -ftest-coverage
endif

# Determine Correct Linking Flag
UNAME = $(shell uname -s)
ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenCL
else ifeq ($(UNAME), Linux)
LDFLAGS = -lOpenCL
endif

# Define Makefile Aliases
default: clean clinfo
all: default examples $(TESTSUITE)
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

# Build the Test Suite
%: $(TEST_DIR)/%.cpp
	@mkdir -p $(TEST_DIR)/$(OUTPUT)
	$(CXX) $(CIFLAGS) $(CCFLAGS) -I$(SOURCE) -I$(TEST_LIB) $< -o $(TEST_DIR)/$(OUTPUT)/$@ $(LDFLAGS)

# Run the Test Suite
test:
	# ./$(OUTPUT)/chlorine
	./$(OUTPUT)/clinfo > /dev/null
	./$(TEST_DIR)/$(OUTPUT)/$(TESTSUITE) --reporter compact

# Build All Examples
examples: subsystem
subsystem:
	$(MAKE) -C examples/
