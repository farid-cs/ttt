CC = cc
CFLAGS = -g -std=c23 -pedantic -Wall -Wextra -Werror -Iexternal
CPPFLAGS = -D_XOPEN_SOURCE -D_DEFAULT_SOURCE

termbox_h = external/termbox2.h
termbox_c = external/termbox2.c
termbox_o = external/termbox2.o

all: ttt ttt-tui

ttt: ttt.o core.o
	${CC} -o ttt ttt.o core.o

ttt-tui: ttt-tui.o core.o ${termbox_o}
	${CC} -o ttt-tui ttt-tui.o core.o ${termbox_o}

.c.o:
	${CC} -o $@ -c ${CFLAGS} ${CPPFLAGS} $<

${termbox_o}: ${termbox_c}
	${CC} -o ${termbox_o} -c ${CFLAGS} ${CPPFLAGS} ${termbox_c}

ttt-tui.o: ttt-tui.c core.h ${termbox_h}
ttt.o: ttt.c core.h
core.o: core.c core.h

clean:
	rm -rf ttt-tui ttt *.o external/*.o

.PHONY: all clean
