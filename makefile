# =====================================
# makefile
# By Austin T. (Github: Knights879)
# =====================================
# Makefiles make it easy to compile and maintain projects.
# To run, use the command 'make', by itself, in whatever
# directory the makefile is in.

# Like other languages, makefiles can utilize variables to make code
# easier to read and maintain.
CC = gcc
CFLAGS = -Wall -I.
DEPS = DataDiagrams.h
OBJS = DataDiagrams.o arrays.o linkedlists.o stacknqueue.o structs.o trees.o
TARGET = dd

# Rather than using functions/methods/objects/classes, makefiles use
# rules to organize code to tell the 'make' command what to do.

# This rule just tells 'make' that if there is a file named 'clean',
# to ignore it. Otherwise it can mess with some our next rules.
.PHONY: all debug clean

# This rule is what will compile everthing
all: $(TARGET)

# This rule adds debug support for use with GDB
debug: CFLAGS += -g
debug: all

# This rule tells 'make' to compile every C file (.c) into
# an object file (.o) with the same name.
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# NOTE: The above rule is automated, meaning it will run for every C file
# in the current directory. This can be done manually by typing out the
# following rule for C file:
# filename.o: filename.c $(DEPS)
# 	$(CC) -c filename.c

# This rule builds the executable by using all the object files created
# by the previous rule.
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# This rule removes all the object files and the executable created
# by the make file. To run, type 'make clean'.
clean:
	rm $(TARGET) $(OBJS)
