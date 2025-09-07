#include <assert.h>
#include <stdlib.h>

#include "termbox2.h"

constexpr int TIMEOUT = 1;

int
main(void)
{
	struct tb_event event = {0};
	int result = 0;

	/* setup */
	assert(tb_init() == TB_OK);

	/* run */
	while (true) {
		result = tb_peek_event(&event, TIMEOUT);
		while (result == TB_OK) {
			switch (event.type) {
			case TB_EVENT_KEY:
				switch (event.ch) {
				case 'q':
					goto cleanup;
				}
			}
			result = tb_peek_event(&event, TIMEOUT);
		}
		assert(result == TB_ERR_NO_EVENT);
		assert(tb_clear() == TB_OK);
		assert(tb_present() == TB_OK);
	}

cleanup:
	assert(tb_shutdown() == TB_OK);

	return EXIT_SUCCESS;
}
