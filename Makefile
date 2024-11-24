CC = cc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra

all: ttt

clean:
	rm -f ttt

.PHONY: all clean
