# Makefile Targets
CHLORINE = chlorine
CLINFO   = clinfo

SOURCE = chlorine
OUTPUT = build
# Configuration Variables
UNAME  = $(shell uname -s)
CFLAGS = -O3 -std=c++11
WFLAGS = -Wall -Wextra -Wpedantic

# Default Makefile Commands
.PHONY: chlorine clinfo clean test
default: clean $(CHLORINE) $(CLINFO)
clean:
	@rm -rf $(OUTPUT) && mkdir $(OUTPUT)
test:
	./$(OUTPUT)/chlorine

# Makefile Target: CHLORINE
$(CHLORINE): $(SOURCE)/chlorine.cpp
	$(CXX) $(CFLAGS) $(WFLAGS) $< -o $(OUTPUT)/$@ $(LFLAGS)

# Makefile Target: CLINFO
$(CLINFO): $(SOURCE)/clinfo.cpp
	$(CXX) $(CFLAGS) $(WFLAGS) $< -o $(OUTPUT)/$@ $(LFLAGS)

# TravisCI Configuration Flags
ifeq ($(TRAVIS), true)
CFLAGS += -g --coverage -fprofile-arcs -ftest-coverage
endif

# Darwin Configuration Flags
ifeq ($(UNAME), Darwin)
LFLAGS += -framework OpenCL
ifeq ($(CXX), c++)
CXX=clang++
endif
endif

# Linux Compiler Flags
ifeq ($(UNAME), Linux)
LFLAGS += -lOpenCL
endif

# Enable Compiler Warnings
ifeq ($(CXX), clang++)
WFLAGS += -Weverything
endif
