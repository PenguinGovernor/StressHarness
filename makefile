CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror
COMPILE = $(CC) $(CFLAGS)

.PHONY: all clean test


all: stress

test: test__flags

# Binaries 

stress:	stress.o flags.o
	$(COMPILE) -o stress stress.o flags.o

test__flags: test__flags.o flags.o
	$(COMPILE) -o test__flags test__flags.o flags.o

# Objects
test__flag.o:	test__flags.c
	$(COMPILE) -c test__flags.c

flags.o:	flags.c
	$(COMPILE) -c flags.c

stress.o:	stress.c
	$(COMPILE) -c stress.c

# Util
clean:
	rm -f *.gch *.o test__flags stress