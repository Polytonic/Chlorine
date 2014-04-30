# Build Configuration
PLATFORM = $(shell uname -s)
TEST_DIR = tests
SOURCE = chlorine
OUTPUT = builds
#
TESTSUITE = \
	vectors	\

# Set Compiler Flags
CCFLAGS := -O3 -std=c++11
CCFLAGS += -Wall -Wextra -Wpedantic

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
	$(CXX) $(CCFLAGS) -I$(SOURCE) $< -o $(TEST_DIR)/$(OUTPUT)/$@ $(LDFLAGS)

test:
	echo Guess what spell I prepared this morning?
