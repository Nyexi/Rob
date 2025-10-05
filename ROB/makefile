# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -IHEADERS
LDFLAGS = -lm

# Executable name
TARGET = ROB 

# Source files
SRCS = main.c HEADERS/funky.c
OBJS = main.o HEADERS/funky.o
HEADERS = HEADERS/funky.h

# Default target
all: $(TARGET)

# Create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile main.c
main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

# Compile funky.c from HEADERS directory
HEADERS/funky.o: HEADERS/funky.c $(HEADERS)
	$(CC) $(CFLAGS) -c HEADERS/funky.c -o HEADERS/funky.o

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Install (if needed)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin (may require sudo)"
	cp $(TARGET) /usr/local/bin/

# Phony targets
.PHONY: all clean install

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Release build with more optimizations
release: CFLAGS += -O3 -ffast-math
release: $(TARGET)
