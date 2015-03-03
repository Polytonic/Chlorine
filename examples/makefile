# Build All Examples in Subdirectories
SUBDIRS := $(wildcard */.)
default: all
all: $(SUBDIRS)
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	make -C $@
