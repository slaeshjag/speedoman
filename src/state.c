#include "speedoman.h"


int stateHandle(void *handle) {
	SPEEDOMAN *s = handle;

	if (s->newstate != s->state) {
		switch (s->state) {
			case STATE_DUMMY:
				break;
			case STATE_SPLASH:
				break;
			default:
				break;
		}

		switch (s->newstate) {
			case STATE_DUMMY:
				break;
			case STATE_SPLASH:
				break;
			default:
				break;
		}
	}

	s->state = s->newstate;
	
	return 0;
}
