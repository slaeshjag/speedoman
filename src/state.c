#include "speedoman.h"


void stateSplash() {
	return;
}


void stateMap() {
	int i;

	for (i = 0; i < s->active_level->layers; i++) {
		d_tilemap_draw(s->active_level->layer[i].tilemap);
		d_render_blend_enable();
		movableLoop(i);
		d_render_blend_disable();
	}
	return;
}


int stateHandle() {

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
			case STATE_TESTGAME:
				levelLoad("maps/test.ldmz");
				movableLoad();
			default:
				break;
		}
	}

	s->state = s->newstate;

	switch (s->state) {
		case STATE_DUMMY:
			break;
		case STATE_SPLASH:
			stateSplash();
			break;
		case STATE_TESTGAME:
			stateMap();
			break;
		default:
			fprintf(stderr, "Unhandled state %i\n", s->state);
			s->newstate = STATE_DUMMY;
			break;
	}
	
	return 0;
}
