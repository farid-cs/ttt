#include <stdio.h>
#include <stdlib.h>

#include "core.h"

static void
consume_line(void)
{
	int c = fgetc(stdin);

	while (c != '\n' && c != EOF)
		c = fgetc(stdin);
}

static bool
scan_index(size_t *index)
{
	int c = 0;

	c = fgetc(stdin);
	if (c < '0' || c > '8') {
		if (c != '\n' && c != EOF)
			consume_line();
		return false;
	}
	*index = c - '0';
	c = fgetc(stdin);
	if (c != '\n') {
		consume_line();
		return false;
	}
	return true;
}

static bool
prompt_for_index(int id)
{
	if (printf("Player #%d: ", id + 1) < 0)
		return false;
	if (fflush(stdout) == EOF)
		return false;
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
print_board(const int *b)
{
	size_t i = 0;

	for (i = 0; i != 9; i += 3)
		if (printf("%c %c %c\n", b[i], b[i+1], b[i+2]) < 0)
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
		if (!prompt_for_index(s.id))
			return EXIT_FAILURE;
		if (scan_index(&index))
			put_at(&s, index);
		else if (feof(stdin))
			return EXIT_SUCCESS;
		else if (ferror(stdin))
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
