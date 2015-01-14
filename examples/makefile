# Build All Examples in Subdirectories
SUBDIRS := $(wildcard */.)
default: all
all: $(SUBDIRS)
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
