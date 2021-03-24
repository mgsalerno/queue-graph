CC = gcc
CFLAGS = -g -Wall -Wextra

source = $(wildcard *.c)
objects = $(source:.c=.o)

# ------------------------------------------------------------------------------

.PHONY: clean

main: $(objects)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(objects) main