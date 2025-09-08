#include <assert.h>
#include <stdlib.h>

#include "termbox2.h"

#include "core.h"

constexpr int TIMEOUT = 1;

static void
print_board(const int *board)
{
	const int *b = board;
	size_t i = 0;

	for (i = 0; i != 3; i++)
		assert(tb_printf(0, i, 0, 0, "%c %c %c", b[i*3], b[i*3+1], b[i*3+2]) == TB_OK);
}

int
main(void)
{
	struct tb_event event = {0};
	int result = 0;
	State s = State_init();

	/* setup */
	assert(tb_init() == TB_OK);

	/* run */
	while (true) {
		while (true) {
			result = tb_peek_event(&event, TIMEOUT);
			if (result != TB_OK)
				break;
			switch (event.type) {
			case TB_EVENT_KEY:
				switch (event.ch) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
					if (s.status == Proceed)
						put_at(&s, event.ch - '0');
					break;
				case 'q':
					goto cleanup;
				}
			}
		}
		assert(result == TB_ERR_NO_EVENT);
		assert(tb_clear() == TB_OK);
		print_board(s.board);
		assert(tb_printf(0, 4, 0, 0, "Press q to quit") == TB_OK);
		if (s.status == Win) {
			assert(tb_printf(0, 5, 0, 0, "Player #%d won", s.id+1) == TB_OK);
		}
		if (s.status == Tie) {
			assert(tb_printf(0, 5, 0, 0, "No winner") == TB_OK);
		}
		assert(tb_present() == TB_OK);
	}

cleanup:
	assert(tb_shutdown() == TB_OK);

	return EXIT_SUCCESS;
}
