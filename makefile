# Makefile Targets
TARGET = chlorine
CLINFO = clinfo
OUTDIR = bin/
INCDIR = lib/

# Configure Compiler Options
SOURCE = src/chlorine.cpp
CLNFOS = src/clinfo.cpp
UNAMES = $(shell uname -s)

# OS X Configuration Flags
ifeq ($(UNAMES), Darwin)
LFLAGS += -framework OpenCL
# Fix Darwin Clang++ Alias
ifeq ($(CXX), c++)
CXX = clang++
endif

# Linux Configuration Flags
else ifeq ($(UNAMES), Linux)
LFLAGS += -lOpenCL
endif

# Clang Compiler Flags
ifeq ($(CXX), clang++)
CFLAGS += -O3 -g -Weverything

# GNU Compiler Flags
else ifeq ($(CXX), g++)
CFLAGS += -O3 -g -Wall -Wextra
endif

# Clear Binary and Build
default: clean $(TARGET) $(CLINFO)
all: default
.PHONY: all

# Compile Source and Flags
$(TARGET): $(SOURCE)
	$(CXX) $(CFLAGS) $< -o $(OUTDIR)$@ $(LFLAGS)

$(CLINFO): $(CLNFOS)
	$(CXX) $(CFLAGS) $< -o $(OUTDIR)$@ $(LFLAGS)

# Remove Generated Files
clean:
	@rm -rf $(OUTDIR)$(TARGET)
	@rm -rf $(OUTDIR)$(TARGET).dSYM
