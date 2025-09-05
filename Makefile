CC = cc
CFLAGS = -g -std=c23 -pedantic -Wall -Wextra -Wconversion -Werror

all: ttt

ttt: ttt.o core.o
	${CC} -o ttt ttt.o core.o

ttt.o: ttt.c core.h
core.o: core.c core.h

clean:
	rm -f ttt *.o

.PHONY: all clean
