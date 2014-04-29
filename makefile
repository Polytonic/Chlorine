# Makefile Targets
CHLORINE = chlorine
CLINFO   = clinfo

SOURCE = src
BUILDS = bin

# Configuration Variables
UNAME  = $(shell uname -s)
CFLAGS = -O3 -std=c++11
WFLAGS = -Wall -Wextra -Wpedantic

# Default Makefile Commands
default: clean $(CHLORINE) $(CLINFO)
.PHONY: clean
clean:
	@rm -rf chlorine
	@rm -rf chlorine.gcno
	@rm -rf chlorine.dSYM
	@rm -rf clinfo
	@rm -rf clinfo.gcno
	@rm -rf clinfo.dSYM

# Makefile Target: CHLORINE
$(CHLORINE): $(SOURCE)/chlorine.cpp
	$(CXX) $(CFLAGS) $(WFLAGS) $< -o $@ $(LFLAGS)

# Makefile Target: CLINFO
$(CLINFO): $(SOURCE)/clinfo.cpp
	$(CXX) $(CFLAGS) $(WFLAGS) $< -o $@ $(LFLAGS)


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
