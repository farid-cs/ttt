#include <stdio.h>

int board[3][3] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
};

void
display_board(void)
{
	for (int i = 0; i != 3; i++) {
		const int *row = board[i];
		printf("%c %c %c\n", row[0], row[1], row[2]);
	}
}

void
draw_on_board(int place, int symbol)
{
	place -= 1;
	board[place/3][place%3] = symbol;
}

int
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

int
main(void)
{
	int player = 0;

	for (;;) {
		int place;
		int symbol = player % 2 ? 'o' : 'x';

		display_board();
		printf("Player #%d's turn: ", player + 1);
		fflush(stdout);
		scanf("%d", &place);
		getchar();
		if (place < 0 || place > 9) {
			fprintf(stderr, "error: ivalid place. Press enter to continue...");
			getchar();
		}
		draw_on_board(place, symbol);
		if (game_over())
			break;
		player = (player + 1) % 2;
	}
	display_board();
	printf("Player #%d won\n", player + 1);
	return 0;
}
