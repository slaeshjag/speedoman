#include "speedoman.h"


void stateSplash() {
	return;
}


void stateStageSelect() {
	stageSelectDraw();
}


void stateMap() {
	int i;
	
	if (!s->var.pause.active && !s->var.respawn.request_respawn) {
		movableLoop();
		bulletLoop();
	}
	
	cameraLoop();

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
	level_respawn_loop();
	d_render_blend_disable();
	meterDrawAll();

	if (s->var.pause.active)
		pausescreen_draw();


	return;
}


int stateHandle() {

	if (s->newstate != s->state) {
		if (d_render_fade_status() != 2) {
			d_render_fade_in(500, 0, 0, 0);
		} else {
			switch (s->state) {
				case STATE_DUMMY:
					break;
				case STATE_SPLASH:
					break;
				case STATE_STAGE_SELECT:
					break;
				case STATE_TESTGAME:
					save_save();
					break;
				default:
					break;
			}
	
			switch (s->newstate) {
				case STATE_DUMMY:
					break;
				case STATE_SPLASH:
					break;
				case STATE_STAGE_SELECT:
					break;
				case STATE_TESTGAME:
					cameraInit();
					levelLoad();
					s->var.respawn.request_respawn = 0;
					movableLoad();
					s->var.pause.active = 0;
					movableFreezeSprites(1);
				default:
					break;
			}
			
			d_render_fade_out(500);
			s->state = s->newstate;
		}
	}


	switch (s->state) {
		case STATE_DUMMY:
			break;
		case STATE_SPLASH:
			stateSplash();
			break;
		case STATE_TESTGAME:
			stateMap();
			break;
		case STATE_STAGE_SELECT:
			stateStageSelect();
			break;
		default:
			fprintf(stderr, "Unhandled state %i\n", s->state);
			s->newstate = STATE_DUMMY;
			break;
	}
	
	return 0;
}
