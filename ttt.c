#include <stdio.h>
#include <stdlib.h>

#include "core.h"

static bool
ask_for_index(int id, size_t *index)
{
	int c = 0;

	if (printf("Player #%d: ", id + 1) < 0)
		return false;
	if (fflush(stdout) == EOF)
		return false;
	c = fgetc(stdin);
	if (c < '0' || c > '8') {
		while (c != '\n' && c != EOF) {
			c = fgetc(stdin);
		}
		return false;
	}
	*index = c - '0';
	c = fgetc(stdin);
	if (c != '\n') {
		while (c != '\n' && c != EOF) {
			c = fgetc(stdin);
		}
		return false;
	}
	return true;
}

static bool
clear_screen(void)
{
	if (printf("\33[H\33[J") < 0)
		return false;
	if (fflush(stdout) == EOF)
		return false;
	return true;
}

static bool
print_board(const int *board)
{
	const int *b = nullptr;

	for (b = board; b != board+9; b += 3)
		if (printf("%c %c %c\n", b[0], b[1], b[2]) < 0)
			return false;
	return true;
}

int
main(void)
{
	size_t index = 0;
	State s = State_init();

	while (s.status == Proceed) {
		if (!clear_screen())
			return EXIT_FAILURE;
		if (!print_board(s.board))
			return EXIT_FAILURE;
		if (ask_for_index(s.id, &index))
			put_at(&s, index);
		else if (feof(stdin))
			return EXIT_SUCCESS;
		else if (ferror(stdin) || ferror(stdout))
			return EXIT_FAILURE;
	}

	if (!clear_screen())
		return EXIT_FAILURE;
	if (!print_board(s.board))
		return EXIT_FAILURE;
	if (s.status == Win) {
		if (printf("Player #%d won\n", s.id + 1) < 0)
			return EXIT_FAILURE;
	} else if (printf("No winner\n") < 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
