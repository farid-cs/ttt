#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "core.h"

static bool
ask_for_index(int id)
{
	size_t index = 0;

	printf("Player #%d: ", id + 1);
	fflush(stdout);
	scanf("%zu", &index);
	return index;
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
		index = ask_for_index(s.id);
		if (index < 9)
			put_at(&s, index);
	}

	print_board(s.board);
	if (s.status == Win)
		printf("Player #%d won\n", s.id + 1);
	else
		printf("No winner\n");

	return EXIT_SUCCESS;
}
