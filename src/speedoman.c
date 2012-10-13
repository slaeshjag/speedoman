#include "speedoman.h"


int speedomanInit(SPEEDOMAN *s) {
	s->newstate = STATE_TESTGAME;
	s->state = STATE_DUMMY;

	s->movable.movable = NULL;
	s->movable.movables = 0;

	return 0;
}


int main(int argc, char **argv) {
	void *handle;
	DARNIT_KEYS keys;
	SPEEDOMAN *s;

	s = malloc(sizeof(SPEEDOMAN));

	if ((handle = darnitInit("Speedoman", "speedoman")) == NULL)
		return -1;
	
	/* Nollställer allt och sätter upp alla strukturer för informationsskärm som visas i början */
	speedomanInit(s);

	for (;;) {
		stateHandle(s);
		keys = darnitButtonGet();
		if (keys.x)
			return 0;
		darnitLoop();
	}

	return 0;
}
