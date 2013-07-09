#include "speedoman.h"


void level_init() {
	int x, y;

	x = d_font_string_w(s->var.font, d_stringtable_entry(s->var.lang, "Ready"));
	x >>= 1;
	x *= -1;
	x += (s->var.screen_w >> 1);
	y = (s->var.screen_h >> 1) + 80;

	s->var.respawn.ready = d_text_surface_new(s->var.font, 20, 200, x, y);
	d_text_surface_string_append(s->var.respawn.ready, d_stringtable_entry(s->var.lang, "Ready"));
	
	x = d_font_string_w(s->var.font, d_stringtable_entry(s->var.lang, "Game over"));
	x >>= 1;
	x *= -1;
	x += (s->var.screen_w >> 1);
	y = (s->var.screen_h >> 1);
	
	s->var.respawn.game_over = d_text_surface_new(s->var.font, 20, 200, x, y);
	d_text_surface_string_append(s->var.respawn.game_over, d_stringtable_entry(s->var.lang, "Game over"));

	return;
}


int levelLoad() {

	if (s->active_level)
		s->active_level = d_map_unload(s->active_level);

	s->camera.x = s->camera.y = 0;
	if (!(s->active_level = d_map_load(s->load_level)))
		return -1;
	
	s->movable.respawn_x = s->movable.respawn_y = -1;
	
	return 0;
}


void level_respawn_loop() {
	if (s->var.respawn.respawn_time <= 0)
		return;
	movableFreezeSprites(1);
	if (s->var.respawn.respawn_time % 500 < 250 && s->var.respawn.request_respawn == 1)
		d_text_surface_draw(s->var.respawn.ready);
	else if (s->var.respawn.request_respawn == -2)
		d_text_surface_draw(s->var.respawn.game_over);
	s->var.respawn.respawn_time -= d_last_frame_time();
	if (s->var.respawn.respawn_time > 0)
		return;
	if (s->var.respawn.request_respawn == -1) {
		s->var.progress.death_count++;
		if ((--s->var.progress.lives) >= 0) {
			s->var.respawn.request_respawn = 0;
			movableRespawn();
		} else {
			s->var.progress.game_over_count++;
			s->var.respawn.request_respawn = -2;
			s->var.respawn.respawn_time = 3000;
			s->var.progress.lives = SPEEDOMAN_START_AMOUNT_LIVES;
		}
	} else if (s->var.respawn.request_respawn == 1) {
		s->var.respawn.request_respawn = 0;
		movableFreezeSprites(0);
	} else if (s->var.respawn.request_respawn == -2)
		s->newstate = STATE_STAGE_SELECT;
	


	return;
}
		
