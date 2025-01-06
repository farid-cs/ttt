#include <stdio.h>

static int board[] = {
	'0', '1', '2',
	'3', '4', '5',
	'6', '7', '8',
};

static void
display_board(void)
{
	for (int i = 0; i < 9; i += 3)
		printf("%c %c %c\n", board[i], board[i+1], board[i+2]);
}

static int
game_over(void)
{
	return
		board[0] == board[1] && board[1] == board[2] ||
		board[3] == board[4] && board[4] == board[5] ||
		board[6] == board[7] && board[7] == board[8] ||
		board[0] == board[3] && board[3] == board[6] ||
		board[1] == board[4] && board[4] == board[7] ||
		board[2] == board[5] && board[5] == board[8] ||
		board[0] == board[4] && board[4] == board[8] ||
		board[2] == board[4] && board[4] == board[6]
	;
}

static int
isempty(int symbol)
{
	return symbol != 'x' && symbol != 'o';
}

static int
take_turn(int player)
{
	int cell;

	display_board();
	printf("Player #%d's turn: ", player + 1);
	fflush(stdout);

	scanf("%d", &cell);
	getchar();

	if (cell < 0 || cell > 8) {
		fprintf(stderr, "error: invalid cell. Press enter to continue...");
		getchar();
		return -1;
	}

	if (!isempty(board[cell])) {
		fprintf(stderr, "error: non empty cell. Press enter to continue...");
		getchar();
		return -1;
	}

	board[cell] = player % 2 ? 'o' : 'x';

	return 0;
}

int
main(void)
{
	int player = 0;

	for (;;) {
		if (take_turn(player))
			continue;
		if (game_over())
			break;
		player ^= 1;
	}

	display_board();
	printf("Player #%d won\n", player + 1);

	return 0;
}
