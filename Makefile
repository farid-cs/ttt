CC = cc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -Wconversion -Werror

all: ttt

clean:
	rm -f ttt

.PHONY: all clean
