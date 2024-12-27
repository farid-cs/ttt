#include <stdio.h>

int board[3][3] = {
	{'0', '1', '2'},
	{'3', '4', '5'},
	{'6', '7', '8'},
};

static void
display_board(void)
{
	for (int i = 0; i != 3; i++) {
		const int *row = board[i];
		printf("%c %c %c\n", row[0], row[1], row[2]);
	}
}

static void
draw_on_board(int cell, int symbol)
{
	board[cell/3][cell%3] = symbol;
}

static int
game_over(void)
{
	return
		board[0][0] == board[0][1] && board[0][1] == board[0][2] ||
		board[1][0] == board[1][1] && board[1][1] == board[1][2] ||
		board[2][0] == board[2][1] && board[2][1] == board[2][2] ||
		board[0][0] == board[1][0] && board[1][0] == board[2][0] ||
		board[0][1] == board[1][1] && board[1][1] == board[2][1] ||
		board[0][2] == board[1][2] && board[1][2] == board[2][2] ||
		board[0][0] == board[1][1] && board[1][1] == board[2][2] ||
		board[0][2] == board[1][1] && board[1][1] == board[2][0]
	;
}

static int
empty_cell(int cell)
{
	int symbol;

	symbol = board[cell/3][cell%3];
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
		fprintf(stderr, "error: ivalid cell. Press enter to continue...");
		getchar();
		return -1;
	}

	if (!empty_cell(cell)) {
		fprintf(stderr, "error: non empty cell. Press enter to continue...");
		getchar();
		return -1;
	}

	draw_on_board(cell, player % 2 ? 'o' : 'x');
	return 0;
}

int
main(void)
{
	int player = 0;

	while (!game_over()) {
		if (take_turn(player))
			continue;
		player ^= 1;
	}

	display_board();
	printf("Player #%d won\n", player + 1);
	return 0;
}
