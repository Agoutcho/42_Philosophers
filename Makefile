CC = gcc
CFLAGS = -Wall -Wextra -pthread

philosophers: philosophers.c
    $(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
    rm -f philosophers
