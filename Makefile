#
# 'make all' - Compile all source file to generate executables
# 'make clean' - Clean executables
#

# Compilation settings
CC = gcc
CFLAGS = -g -Wall
LDLIBS = -lcups

# targets to build
TARGET = get-printer-attributes

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDLIBS)

.PHONY: clean

# clean executables
clean:
	$(RM) $(TARGET)