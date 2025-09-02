#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "core.h"

static bool
get_index(size_t *index)
{
	scanf("%zu", index);
	if (*index > 8)
		return false;
	return true;
}

static void
print_board(const int *board)
{
	const int *b = NULL;

	for (b = board; b != board+9; b += 3)
		printf("%c %c %c\n", b[0], b[1], b[2]);
}

int
main(void)
{
	static size_t index = 0;
	static State s = {
		.board = { '0', '1', '2', '3', '4', '5', '6', '7', '8' },
		.id = 0,
		.status = Proceed,
	};

	while (s.status == Proceed) {
		print_board(s.board);
		printf("Player #%d: ", s.id + 1);
		fflush(stdout);
		if (get_index(&index))
			put_at(&s, index);
	}

	print_board(s.board);
	if (s.status == Win)
		printf("Player #%d won\n", s.id + 1);
	else
		printf("No winner\n");

	return EXIT_SUCCESS;
}
