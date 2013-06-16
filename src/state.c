#include "speedoman.h"


void stateSplash() {
	return;
}


void stateMap() {
	int i;
	
	movableLoop();
	cameraLoop();
	bulletLoop();

	for (i = 0; i < s->active_level->layers; i++) {
		d_tilemap_camera_move(s->active_level->layer[i].tilemap, s->camera.x, s->camera.y);
		d_tilemap_draw(s->active_level->layer[i].tilemap);
		d_render_offset(s->camera.x, s->camera.y);
		d_render_blend_enable();
		movableLoopRender(i);
		d_render_blend_disable();
		d_render_offset(0, 0);
	}

	d_render_blend_enable();
	bulletDraw();
	d_render_blend_disable();


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
				cameraInit();
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
