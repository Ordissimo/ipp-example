#
# 'make all' - Compile all source file to generate executables
# 'make clean' - Clean executables
#

# Compilation settings
CC = gcc
CFLAGS = -g -Wall
LDLIBS = -lcups

# targets to build
TARGETS = get-printer-attributes print-job

all: $(TARGETS)

.PHONY: clean

# clean executables
clean:
	$(RM) $(TARGETS)