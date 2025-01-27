#include <stdio.h>

static void
display_board(const int *board)
{
	for (int i = 0; i < 9; i += 3)
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
	int player = 0;

	for (;;) {
		int pos;

		display_board(board);
		printf("Player #%d's turn: ", player + 1);
		fflush(stdout);

		scanf("%d", &pos);
		getchar();

		if (pos < 0 || pos > 8) {
			fprintf(stderr, "error: invalid cell. Press enter to continue...");
			getchar();
			continue;
		}

		if (!isempty(board[pos])) {
			fprintf(stderr, "error: non empty cell. Press enter to continue...");
			getchar();
			continue;
		}

		board[pos] = player % 2 ? 'o' : 'x';

		if (game_over(board))
			break;
		player ^= 1;
	}

	display_board(board);
	printf("Player #%d won\n", player + 1);

	return 0;
}
