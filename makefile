# Makefile Targets
CHLORINE = chlorine
CLINFO   = clinfo

# Target Directories
SOURCES = sources
HEADERS = headers

# Configuration Variables
UNAME = $(shell uname -s)

# Default Makefile Commands
default: clean $(CHLORINE) $(CLINFO)
clean:
	@rm -rf $(CHLORINE)
	@rm -rf $(CHLORINE).dSYM
	@rm -rf $(CLINFO)
	@rm -rf $(CLINFO).dSYM

# Makefile Target: CHLORINE
$(CHLORINE): $(SOURCES)/$(CHLORINE).cpp
	$(CXX) $(CFLAGS) -I$(HEADERS) $< -o $@ $(LFLAGS)

# Makefile Target: CLINFO
$(CLINFO): $(SOURCES)/$(CLINFO).cpp
	$(CXX) $(CFLAGS) -I$(HEADERS) $< -o $@ $(LFLAGS)

# Darwin Configuration Flags
ifeq ($(UNAME), Darwin)
LFLAGS += -framework OpenCL
endif

# Linux Compiler Flags
ifeq ($(UNAME), Linux)
LFLAGS += -lOpenCL
endif

# Enable Compiler Warnings
ifeq ($(CXX), g++)
CFLAGS += -O3 -Wall -Wextra -Wpedantic
else # Implicitly Clang++
CFLAGS += -O3 -Weverything
endif
