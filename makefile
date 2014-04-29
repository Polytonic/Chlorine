# Makefile Targets
CHLORINE = chlorine
CLINFO   = clinfo

SOURCE = src
BUILDS = bin

# Configuration Variables
UNAME  = $(shell uname -s)
CFLAGS = -O3 -std=c++11

# Default Makefile Commands
default: clean $(CHLORINE) $(CLINFO)
.PHONY: clean
clean:
	@rm -rf chlorine
	@rm -rf clinfo

# Makefile Target: CHLORINE
$(CHLORINE): $(SOURCE)/chlorine.cpp
	$(CXX) $(CFLAGS) $< -o $@ $(LFLAGS)

# Makefile Target: CLINFO
$(CLINFO): $(SOURCE)/clinfo.cpp
	$(CXX) $(CFLAGS) $< -o $@ $(LFLAGS)

# Darwin Configuration Flags
ifeq ($(UNAME), Darwin)
LFLAGS += -framework OpenCL
endif

# Linux Compiler Flags
ifeq ($(UNAME), Linux)
LFLAGS += -lOpenCL
endif

# Enable Compiler Warnings
ifeq ($(CXX), clang++)
CFLAGS += -Weverything
else ifeq ($(CXX), g++)
CFLAGS += -Wall -Wextra -Wpedantic
endif
