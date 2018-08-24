CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror
COMPILE = $(CC) $(CFLAGS)

.PHONY: all clean test


all: test

test: test__flags

# Binaries 

test__flags: test__flags.o flags.o
	$(COMPILE) -o test__flags test__flags.o flags.o

# Objects
test__flag.o:	test__flags.c
	$(COMPILE) -c test__flags.c

flags.o:	flags.c
	$(COMPILE) -c flags.c

# Util
clean:
	rm -f *.gch *.o test__flags