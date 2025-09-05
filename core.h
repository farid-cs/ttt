#ifndef TTT_CORE_H
#define TTT_CORE_H

#include <stddef.h>

typedef enum Status {
	Proceed,
	Win,
	Tie,
} Status;

typedef struct State {
	int board[9];
	int id;
	Status status;
} State;

State State_init(void);
void put_at(State *s, size_t index);

#endif
