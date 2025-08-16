#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int board[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
static int player_id = 0;
static bool win = false;
static bool tie = false;

static bool
crossed(void)
{
	return (board[0] == board[1] && board[1] == board[2]) ||
		(board[3] == board[4] && board[4] == board[5]) ||
		(board[6] == board[7] && board[7] == board[8]) ||
		(board[0] == board[3] && board[3] == board[6]) ||
		(board[1] == board[4] && board[4] == board[7]) ||
		(board[2] == board[5] && board[5] == board[8]) ||
		(board[0] == board[4] && board[4] == board[8]) ||
		(board[2] == board[4] && board[4] == board[6]);
}

static bool
isemptyat(size_t pos)
{
	return board[pos] != 'x' && board[pos] != 'o';
}

static void
put_at(size_t pos)
{
	if (!isemptyat(pos))
		return;
	if (player_id)
		board[pos] = 'o';
	else
		board[pos] = 'x';
	if (crossed()) {
		win = true;
		return;
	}
	for (size_t i = 0; i != 9; i++) {
		if (isemptyat(i)) {
			player_id = !player_id;
			return;
		}
	}
	tie = true;
}

static int
get_pos(size_t *pos)
{
	printf("Player #%d: ", player_id + 1);
	fflush(stdout);
	scanf("%zu", pos);
	getchar();
	if (*pos > 8)
		return -1;
	return 0;
}

static void
update(void)
{
	size_t pos = -1;

	if (get_pos(&pos) < 0)
		return;
	put_at(pos);
}

static void
print_board(void)
{
	int *b = NULL;

	for (b = board; b != board+9; b += 3)
		printf("%c %c %c\n", b[0], b[1], b[2]);
}

int
main(void)
{
	while (!win && !tie) {
		print_board();
		update();
	}

	print_board();
	if (win)
		printf("Player #%d won\n", player_id + 1);
	else
		printf("No winner\n");

	return EXIT_SUCCESS;
}
