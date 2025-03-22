#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void
display_board(const int *board)
{
	for (size_t i = 0; i < 9; i += 3)
		printf("%c %c %c\n", board[i], board[i+1], board[i+2]);
}

static int
game_over(const int *board)
{
	return
		board[0] == board[1] && board[1] == board[2] ||
		board[3] == board[4] && board[4] == board[5] ||
		board[6] == board[7] && board[7] == board[8] ||
		board[0] == board[3] && board[3] == board[6] ||
		board[1] == board[4] && board[4] == board[7] ||
		board[2] == board[5] && board[5] == board[8] ||
		board[0] == board[4] && board[4] == board[8] ||
		board[2] == board[4] && board[4] == board[6];
}

static int
isempty(int c)
{
	return c != 'x' && c != 'o';
}

int
main(void)
{
	int board[] = {
		'0', '1', '2',
		'3', '4', '5',
		'6', '7', '8',
	};
	int player_id = 0;

	for (;;) {
		size_t pos = -1;

		display_board(board);
		printf("Player #%d's turn: ", player_id + 1);
		fflush(stdout);

		scanf("%zu", &pos);
		getchar();

		if (pos > 8 || !isempty(board[pos]))
			continue;

		board[pos] = !player_id ? 'x' : 'o';

		if (game_over(board))
			break;

		player_id = !player_id;
	}

	display_board(board);
	printf("Player #%d won\n", player_id + 1);

	return EXIT_SUCCESS;
}
