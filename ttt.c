#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum Status {
	Proceed,
	Win,
	Tie,
} Status;

static int board[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
static int id = 0;
static Status status = Proceed;

static bool row(size_t i, size_t j, size_t k)
{
	return board[i] == board[j] && board[j] == board[k];
}

static bool
any_row(void)
{
	return row(0, 1, 2) || row(3, 4, 5) || row(6, 7, 8)
		|| row(0, 3, 6) || row(1, 4, 7) || row(2, 5, 8)
		|| row(0, 4, 8) || row(2, 4, 6);
}

static bool
isemptyat(size_t index)
{
	return board[index] != 'x' && board[index] != 'o';
}

static void
put_at(size_t index)
{
	if (!isemptyat(index))
		return;
	if (id)
		board[index] = 'o';
	else
		board[index] = 'x';
	if (any_row()) {
		status = Win;
		return;
	}
	for (size_t i = 0; i != 9; i++) {
		if (isemptyat(i)) {
			id += 1;
			id %= 2;
			return;
		}
	}
	status = Tie;
}

static bool
get_index(size_t *index)
{
	printf("Player #%d: ", id + 1);
	fflush(stdout);
	scanf("%zu", index);
	if (*index > 8)
		return -1;
	return 0;
}

static void
update(void)
{
	size_t index = 0;

	if (get_index(&index))
		put_at(index);
}

static void
print_board(void)
{
	const int *b = NULL;

	for (b = board; b != board+9; b += 3)
		printf("%c %c %c\n", b[0], b[1], b[2]);
}

int
main(void)
{
	while (status == Proceed) {
		print_board();
		update();
	}

	print_board();
	if (status == Win)
		printf("Player #%d won\n", id + 1);
	else
		printf("No winner\n");

	return EXIT_SUCCESS;
}
