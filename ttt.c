#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "core.h"

static bool
ask_for_index(int id, size_t *index)
{
	printf("Player #%d: ", id + 1);
	fflush(stdout);
	scanf("%zu", index);
	return *index < 9;
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
	size_t index = 0;
	State s = State_init();

	while (s.status == Proceed) {
		print_board(s.board);
		if (ask_for_index(s.id, &index))
			put_at(&s, index);
	}

	print_board(s.board);
	if (s.status == Win)
		printf("Player #%d won\n", s.id + 1);
	else
		printf("No winner\n");

	return EXIT_SUCCESS;
}
