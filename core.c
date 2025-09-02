#include <stdbool.h>

#include "core.h"

static bool
row(State *s, size_t i, size_t j, size_t k)
{
	return s->board[i] == s->board[j] && s->board[j] == s->board[k];
}

static bool
any_row(State *s)
{
	return row(s, 0, 1, 2) || row(s, 3, 4, 5) || row(s, 6, 7, 8)
		|| row(s, 0, 3, 6) || row(s, 1, 4, 7) || row(s, 2, 5, 8)
		|| row(s, 0, 4, 8) || row(s, 2, 4, 6);
}

static bool
isemptyat(State *s, size_t index)
{
	return s->board[index] != 'x' && s->board[index] != 'o';
}

void
put_at(State *s, size_t index)
{
	if (!isemptyat(s, index))
		return;
	if (s->id)
		s->board[index] = 'o';
	else
		s->board[index] = 'x';
	if (any_row(s)) {
		s->status = Win;
		return;
	}
	for (size_t i = 0; i != 9; i++) {
		if (isemptyat(s, i)) {
			s->id += 1;
			s->id %= 2;
			return;
		}
	}
	s->status = Tie;
}
