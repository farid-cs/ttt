#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int board[] = {
	'0', '1', '2',
	'3', '4', '5',
	'6', '7', '8',
};
int player_id = 0;
size_t pos;
int quit = 0;
int win = 0;

static void
display(void)
{
	for (size_t i = 0; i < 9; i += 3)
		printf("%c %c %c\n", board[i], board[i+1], board[i+2]);
	if (win) {
		printf("Player #%d won\n", player_id + 1);
	} else {
		printf("Player #%d: ", player_id + 1);
		fflush(stdout);
	}
}

static int
crossed(void)
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

void
update(void)
{
	if (win) {
		quit = 1;
		return;
	}

	pos = -1;
	scanf("%zu", &pos);
	getchar();

	if (pos > 8 || !isempty(board[pos]))
		return;

	board[pos] = !player_id ? 'x' : 'o';

	if (crossed()) {
		win = 1;
		return;
	}

	player_id = !player_id;
}

int
main(void)
{
	while (!quit) {
		display();
		update();
	}

	return EXIT_SUCCESS;
}
