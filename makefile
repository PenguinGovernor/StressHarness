.DEFAULT_GOAL := stress
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror
COMPILE = $(CC) $(CFLAGS)

.PHONY: all clean test


all: stress test

test: test__flags test__circles

# Binaries 

stress:	stress.o flags.o
	$(COMPILE) -o stress stress.o flags.o

# Testing Bins

test__circles: test__circles.o circles.o
	$(COMPILE) -o test__circles test__circles.o circles.o -lm

test__flags: test__flags.o flags.o
	$(COMPILE) -o test__flags test__flags.o flags.o

# Test Objects
test__circles.o:	test__circles.c
	$(COMPILE) -c test__circles.c -lm

test__flag.o:	test__flags.c
	$(COMPILE) -c test__flags.c

# Lib Objects

circles.o:	circles.c
	$(COMPILE) -c circles.c -lm

flags.o:	flags.c
	$(COMPILE) -c flags.c

# Main bin objs

stress.o:	stress.c
	$(COMPILE) -c stress.c

# Util
clean:
	rm -f *.gch *.o test__flags test__circles stress 